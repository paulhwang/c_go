/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tcp_connect_class.cpp
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include "../../phwang.h"
#include "../../define_dir/logo_def.h"
#include "tcp_connect_class.h"
#include "../port_dir/port_class.h"

TcpConnectClass::TcpConnectClass (char const *who_val)
{
    memset(this, 0, sizeof(*this));
    this->theWho = who_val;
    phwangDebugWS(false, "TcpConnectClass::TcpConnectClass", this->theWho, "init");
}

TcpConnectClass::~TcpConnectClass (void)
{
    phwangDebugWS(false, "~TcpConnectClass::~TcpConnectClass", this->theWho, "exit");
}

#define PHWANG_TP_CONNECT_RETRY_MAX_COUNT 30

void *TcpConnectClass::tcpConnect (
        int debug_on_val,
        unsigned long ip_addr_val, 
        unsigned short port_val, 
        void (*receive_callback_val)(void *, void *, void *), 
        void *receive_object_val,
        char const *who_val)
{
    int s;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    this->debugOn_ = true && debug_on_val;
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        phwangLogitWS("TcpConnectClass::tcpConnect", this->theWho, "open socket error");
        return 0;
    }
 
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_val);
  
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        phwangLogitWS("TcpConnectClass::tcpConnect", this->theWho, " Invalid address/ Address not supported");
        return 0;
    }
  
    phwangDebugWS(false, "TcpConnectClass::tcpConnect", this->theWho, "connecting");

    int retry_count = PHWANG_TP_CONNECT_RETRY_MAX_COUNT;
    while (retry_count) {
        if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            if (!retry_count--) {
                phwangLogitWS("TcpConnectClass::tcpConnect", this->theWho, "Failed");
                return 0;
            }
            else {
                phwangLogitWS("TcpConnectClass::tcpConnect", this->theWho, "retry-----");
                sleep(1);
            }
        }
        else {
            break;
        }
    }

    if (true && this->debugOn_) {
        printf("TcpConnectClass::tcpConnect(%s) connected!\n", this->theWho);
    }

    send(s, LOGO_DEF::PHWANG_LOGO , strlen(LOGO_DEF::PHWANG_LOGO) , 0);

    PortClass *tp_transfer_object = new PortClass(this->debugOn_, s, receive_callback_val, receive_object_val, who_val);
    tp_transfer_object->startThreads(PortClass::CLIENT_INDEX);
    return tp_transfer_object;
}
