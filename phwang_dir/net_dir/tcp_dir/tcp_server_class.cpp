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
#include "tcp_server_class.h"
#include "../port_dir/port_class.h"

#define MAXHOSTNAME 32
#define BACKLOG 5

TcpServerClass::TcpServerClass (
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
    this->theTpTransferObjectIndex = PortClass::SERVER_INDEX;

    phwangDebugWS(false, "TcpServerClass::TcpServerClass", this->theWho, "init");
}

TcpServerClass::~TcpServerClass (void)
{
}

void *transportServerThreadFunction (void *tp_server_object_val)
{
    return ((TcpServerClass *) tp_server_object_val)->serverThreadFunction(0);
}

void TcpServerClass::startServerThread (void)
{
    phwangDebugWS(false, "TcpServerClass::startServerThread", this->theWho, "start");

    int r = phwangPthreadCreate(&this->theServerThread, 0, transportServerThreadFunction, this);
    if (r) {
        printf("Error - startServerThread() return code: %d\n", r);
        return;
    }
}

void *TcpServerClass::serverThreadFunction (void *data_val)
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
        phwangLogitWS("TcpServerClass::serverThreadFunction", this->theWho, s);
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        phwangLogitWS("TcpServerClass::serverThreadFunction", this->theWho, "open socket error");
        return 0;
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        phwangLogitWS("TcpServerClass::serverThreadFunction", this->theWho, "setsockopt error");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->thePort);

    if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
        phwangLogitWS("TcpServerClass::serverThreadFunction", this->theWho, "bind error");
        return 0;
    }

    while (1) {
        if (0) { /* debug */
            char s[128];
            sprintf(s, "listening for (%s)", this->theWho);
            phwangLogitWS("TcpServerClass::serverThreadFunction", this->theWho, s);
        }

        listen(s, BACKLOG);

        phwangDebugWS(false, "TcpServerClass::serverThreadFunction", this->theWho, "accepting");

        if ((data_socket = accept(s, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            phwangLogitWS("TcpServerClass::serverThreadFunction", this->theWho, "accept error");
            return 0;
        }

        if (1) { /* debug */
            char s[128];
            sprintf(s, "accepted port=%d", this->thePort);
            phwangDebugWS(true, "TcpServerClass::serverThreadFunction", this->theWho, s);
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
                phwangLogitWS("TcpServerClass::serverThreadFunction", this->theWho, s);
            }
            close(data_socket);
            continue;
        }

        PortClass *tp_transfer_object = new PortClass(data_socket, this->theReceiveCallbackFunc, this->theCallerObject, this->theWho);
        tp_transfer_object->startThreads(this->theTpTransferObjectIndex);
        this->theTpTransferObjectIndex++;
        this->theAcceptCallbackFunc(this->theCallerObject, tp_transfer_object);
    }

    //free(data_val);
    return 0;
}
