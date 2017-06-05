/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_server_class.cpp
*/

#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <pwd.h>
#include "tp_transfer_class.h"
#include "../../phwang_dir/phwang.h"
#include "tp_server_class.h"

#define MAXHOSTNAME 32
#define BACKLOG 5

TpClass::TpClass (void *main_object_val)
{
    this->theMainObject = main_object_val;

    if (1) {
        this->logit("TpClass", "init");
    }
}

TpClass::~TpClass (void)
{
}

void *transportServerThreadFunction (void *data_val)
{
    unsigned short port = ((transport_thread_parameter *) data_val)->port;
    TpClass *transport_object = ((transport_thread_parameter *) data_val)->transport_object;
    TpTransferClass *tp_transfer_object = ((transport_thread_parameter *) data_val)->tp_transfer_object;
    free(data_val);

    transport_object->serverThreadFunction(port, tp_transfer_object);
}

pthread_t TpClass::startServerThread (TpTransferClass *tp_transfer_object_val, unsigned short port_val)
{
    pthread_t thread;

    transport_thread_parameter *data = (transport_thread_parameter *) malloc(sizeof(transport_thread_parameter));
    data->port = port_val;
    data->transport_object = this;
    data->tp_transfer_object = tp_transfer_object_val;

    int r;
    if (0) {
        this->logit("startServerThread", "");
    }
    r = pthread_create(&thread, 0, transportServerThreadFunction, data);
    if (r) {
        printf("Error - startServerThread() return code: %d\n", r);
        return 0;
    }

    return thread;
}

TpTransferClass *TpClass::startServer (unsigned short port_val,
                                       void (*receive_callback_val)(void *, void *),
                                       void *receive_object_val,
                                       StartServerOutputStruct *output_val)
{
    pthread_t thread;

    TpTransferClass *tp_transfer_object = new TpTransferClass(this, receive_callback_val, receive_object_val);
    if (tp_transfer_object) {
        thread = this->startServerThread(tp_transfer_object, port_val);
        if (thread) {
            output_val->tp_transfer_object = tp_transfer_object;
            output_val->server_thread = thread;
            return tp_transfer_object;
        }
    }
    else {
        return 0;
    }
}

void TpClass::serverThreadFunction (unsigned short port_val, TpTransferClass *tp_transfer_object_val)
{
  char localhost[MAXHOSTNAME + 1];
  struct servent *sp;
  int s, data_socket;
  struct hostent *hp;
  int opt = 1;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[1024] = {0};

  this->logit("startServer", "start");

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    this->logit("startServer", "open socket error");
    return;
  }

  if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    this->logit("startServer", "setsockopt error");
    return;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port_val);

  if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
    this->logit("startServer", "bind error");
    return;
  }

  this->logit("startServer", "listening");
  listen(s, BACKLOG);

  this->logit("startServer", "accepting");
  if ((data_socket = accept(s, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
    this->logit("startServer", "accept error");
    return;
  }

    this->logit("startServer", "accepted");

    tp_transfer_object_val->startThreads(data_socket);
}

void TpClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void TpClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}

