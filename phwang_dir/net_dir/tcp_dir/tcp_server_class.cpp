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
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/abend_dir/abend_class.h"
#include "tcp_server_class.h"
#include "../tp_dir/tp_transfer_class.h"

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
    memset(this, 0, sizeof(*this));
    this->theCallerObject = caller_object_val;
    this->thePort = port_val;
    this->theAcceptCallbackFunc = accept_callback_func_val;
    this->theReceiveCallbackFunc = receive_callback_func_val;
    this->theAcceptCallbackParameter = accept_callback_parameter_val;
    this->theReceiveCallbackParameter = receive_callback_parameter_val;
    this->theWho = who_val;
    this->theTpTransferObjectIndex = 1;

    this->debug(false, "TpServerClass", "init");
}

TpServerClass::~TpServerClass (void)
{
}

void *transportServerThreadFunction (void *tp_server_object_val)
{
    return ((TpServerClass *) tp_server_object_val)->serverThreadFunction(0);
}

void TpServerClass::startServerThread (void)
{
    this->debug(false, "startServerThread", "");

    int r = phwangPthreadCreate(&this->theServerThread, 0, transportServerThreadFunction, this);
    if (r) {
        printf("Error - startServerThread() return code: %d\n", r);
        return;
    }
}

void *TpServerClass::serverThreadFunction (void *data_val)
{
    char localhost[MAXHOSTNAME + 1];
    struct servent *sp;
    int s, data_socket;
    struct hostent *hp;
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if (0) { /* debug */
        char s[128];
        sprintf(s, "starts for (%s)", this->theWho);
        this->logit("serverThreadFunction", s);
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        this->logit("serverThreadFunction", "open socket error");
        return 0;
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        this->logit("serverThreadFunction", "setsockopt error");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->thePort);

    if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
        this->logit("serverThreadFunction", "bind error");
        return 0;
    }

    while (1) {
        if (0) { /* debug */
            char s[128];
            sprintf(s, "listening for (%s)", this->theWho);
            this->logit("serverThreadFunction", s);
        }

        listen(s, BACKLOG);

        this->debug(true, "serverThreadFunction", "accepting");

        if ((data_socket = accept(s, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            this->logit("serverThreadFunction", "accept error");
            return 0;
        }

        if (1) { /* debug */
            char s[128];
            sprintf(s, "accepted port=%d", this->thePort);
            this->logit("serverThreadFunction", s);
        }

        char data[strlen(TP_PHWANG_LOGO) + 16];
        int length = read(data_socket, data, strlen(TP_PHWANG_LOGO) + 8);
        if (length >= 0) {
            data[length] = 0;
        }
        if ((length != strlen(TP_PHWANG_LOGO)) || (strcmp(data, TP_PHWANG_LOGO))) {
            if (1) { /* debug */
                char s[128];
                sprintf(s, "### Attack: (%s) port=%d data_length=%d data=%s", this->theWho, this->thePort, length, data);
                this->logit("serverThreadFunction", s);
            }
            close(data_socket);
            continue;
        }

        TpTransferClass *tp_transfer_object = new TpTransferClass(data_socket, this->theReceiveCallbackFunc, this->theCallerObject, this->theWho);
        tp_transfer_object->startThreads(this->theTpTransferObjectIndex);
        this->theTpTransferObjectIndex++;
        this->theAcceptCallbackFunc(this->theCallerObject, tp_transfer_object);
    }

    //free(data_val);
    return 0;
}

void TpServerClass::debug (int debug_on_val, char const *func_name_val, char const *str1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebug(debug_on_val, s, str1_val);
    }
}

void TpServerClass::debug2 (int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebug2(debug_on_val, s, str1_val, str2_val);
    }
}

void TpServerClass::debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebugInt(debug_on_val, s, str1_val, int1_val);
    }
}

void TpServerClass::debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebugInt2(debug_on_val, s, str1_val, int1_val, str2_val, int2_val);
    }
}

void TpServerClass::logit (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogit(s, str1_val);
}

void TpServerClass::logit2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogit2(s, str1_val, str2_val);
}

void TpServerClass::logitInt(char const *func_name_val, char const *str1_val, int int1_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogitInt(s, str1_val, int1_val);
}

void TpServerClass::logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogitInt2(s, str1_val, int1_val, str2_val, int2_val);
}

void TpServerClass::abend (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangAbend(s, str1_val);
}

void TpServerClass::abend2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangAbend2(s, str1_val, str2_val);
}
