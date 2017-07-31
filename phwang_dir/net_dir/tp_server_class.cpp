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
                    void (*receive_callback_func_val)(void *, void *, void *),
                    void *receive_callback_parameter_val,
                    char const *who_val)

{
    this->theCallerObject = caller_object_val;
    this->thePort = port_val;
    this->theAcceptCallbackFunc = accept_callback_func_val;
    this->theReceiveCallbackFunc = receive_callback_func_val;
    this->theAcceptCallbackParameter = accept_callback_parameter_val;
    this->theReceiveCallbackParameter = receive_callback_parameter_val;
    this->theWho = who_val;
    this->theTpTransferObjectIndex = 1;

    if (1) {
        this->logit(who_val, "TpServerClass=====");
        this->logit("TpServerClass", "init");
    }
}

TpServerClass::~TpServerClass (void)
{
}

void *transportServerThreadFunction (void *tp_server_object_val)
{
    ((TpServerClass *) tp_server_object_val)->serverThreadFunction(0);
}

void TpServerClass::startServerThread (void)
{
    if (0) {
        this->logit("startServerThread", "");
    }

    int r = pthread_create(&this->theServerThread, 0, transportServerThreadFunction, this);
    if (r) {
        printf("Error - startServerThread() return code: %d\n", r);
        return;
    }
}

void TpServerClass::serverThreadFunction (void *data_val)
{
    char localhost[MAXHOSTNAME + 1];
    struct servent *sp;
    int s, data_socket;
    struct hostent *hp;
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    this->logit("serverThreadFunction", "start");

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        this->logit("serverThreadFunction", "open socket error");
        return;
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        this->logit("serverThreadFunction", "setsockopt error");
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->thePort);

    if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
        this->logit("serverThreadFunction", "bind error");
        return;
    }

    while (1) {
        this->logit("serverThreadFunction", "listening");
        listen(s, BACKLOG);

        this->logit("serverThreadFunction", "accepting");
        if ((data_socket = accept(s, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            this->logit("serverThreadFunction", "accept error");
            return;
        }

        this->logit("serverThreadFunction", "accepted");
        this->logit("serverThreadFunction", this->theWho);

        TpTransferClass *tp_transfer_object = new TpTransferClass(data_socket, this->theReceiveCallbackFunc, this->theCallerObject);
        tp_transfer_object->startThreads(this->theTpTransferObjectIndex);
        this->theTpTransferObjectIndex++;
        this->theAcceptCallbackFunc(this->theCallerObject, tp_transfer_object);
    }

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

