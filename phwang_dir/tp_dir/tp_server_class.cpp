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

TpServerClass::TpServerClass (
                    void *caller_object_val,
                    unsigned short port_val,
                    void (*accept_callback_func_val)(void *, void *),
                    void *accept_callback_parameter_val,
                    void (*receive_callback_func_val)(void *, void *),
                    void *receive_callback_parameter_val)

{
    this->theCallerObject = caller_object_val;
    this->thePort = port_val;
    this->theAcceptCallbackFunc = accept_callback_func_val;
    this->theReceiveCallbackFunc = receive_callback_func_val;
    this->theAcceptCallbackParameter = 0;
    this->theReceiveCallbackParameter = 0;


    if (1) {
        this->logit("TpServerClass", "init");
    }
}

TpServerClass::~TpServerClass (void)
{
}

void *transportServerThreadFunction (void *data_val)
{
    ((tp_server_thread_parameter *) data_val)->tp_server_object->serverThreadFunction(data_val);
}

pthread_t TpServerClass::startServerThread (unsigned short port_val,
                                            void (*accept_callback_func_val)(void *, void *),
                                            void *accept_callback_parameter_val,
                                            void (*receive_callback_func_val)(void *, void *),
                                            void *receive_callback_parameter_val)
{
    pthread_t thread;
    tp_server_thread_parameter *data = (tp_server_thread_parameter *) malloc(sizeof(tp_server_thread_parameter));

    data->tp_server_object = this;
    data->port = port_val;
    data->accept_callback_func = accept_callback_func_val;
    data->accept_callback_parameter = accept_callback_parameter_val;
    data->receive_callback_func = receive_callback_func_val;
    data->receive_callback_parameter = receive_callback_parameter_val;

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

void TpServerClass::serverThreadFunction (void *data_val)
{
    tp_server_thread_parameter *data = (tp_server_thread_parameter *) data_val;
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
    address.sin_port = htons(this->thePort);

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

    TpTransferClass *tp_transfer_object = new TpTransferClass(data_socket, this->theReceiveCallbackFunc, this->theCallerObject);
    tp_transfer_object->startThreads();
    this->theAcceptCallbackFunc(this->theCallerObject, tp_transfer_object);
    free(data_val);
}

void TpServerClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void TpServerClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}

