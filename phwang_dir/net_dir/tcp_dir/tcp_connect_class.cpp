/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tcp_connect_class.cpp
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/abend_dir/abend_class.h"
#include "tcp_connect_class.h"
#include "../tp_phwang_logo.h"
#include "../tp_transfer_class.h"

TcpConnectClass::TcpConnectClass (char const *who_val)
{
    memset(this, 0, sizeof(*this));
    this->theWho = who_val;
    this->debug(false, "TcpConnectClass", "init");
}

TcpConnectClass::~TcpConnectClass (void)
{
    this->debug(false, "~TcpConnectClass", "exit");
}

#define PHWANG_TP_CONNECT_RETRY_MAX_COUNT 30

void *TcpConnectClass::tcpConnect (
                    unsigned long ip_addr_val, 
                    unsigned short port_val, 
                    void (*receive_callback_val)(void *, void *, void *), 
                    void *receive_object_val,
                    char const *who_val)
{
    int s;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        phwangLogit(who_val, "tpConnect() open socket error");
        return 0;
    }
 
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_val);
  
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        phwangLogit(who_val, "tpConnect() Invalid address/ Address not supported \n");
        return 0;
    }
  
    this->debug(true, "tcpConnect", "connecting");

    int retry_count = PHWANG_TP_CONNECT_RETRY_MAX_COUNT;
    while (retry_count) {
        if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            if (!retry_count--) {
                phwangLogit(who_val, "tpConnect() Failed \n");
                return 0;
            }
            else {
                phwangLogit(who_val, "tpConnect() retry-----");
                sleep(1);
            }
        }
        else {
            break;
        }
    }

    this->debug(true, "tcpConnect", "connected");

    send(s, TP_PHWANG_LOGO , strlen(TP_PHWANG_LOGO) , 0);

    TpTransferClass *tp_transfer_object = new TpTransferClass(s, receive_callback_val, receive_object_val, who_val);
    tp_transfer_object->startThreads(0);
    return tp_transfer_object;
}

void TcpConnectClass::debug (int debug_on_val, char const *func_name_val, char const *str1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebug(debug_on_val, s, str1_val);
    }
}

void TcpConnectClass::debug2 (int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebug2(debug_on_val, s, str1_val, str2_val);
    }
}

void TcpConnectClass::debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebugInt(debug_on_val, s, str1_val, int1_val);
    }
}

void TcpConnectClass::debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebugInt2(debug_on_val, s, str1_val, int1_val, str2_val, int2_val);
    }
}

void TcpConnectClass::logit (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogit(s, str1_val);
}

void TcpConnectClass::logit2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogit2(s, str1_val, str2_val);
}

void TcpConnectClass::logitInt(char const *func_name_val, char const *str1_val, int int1_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogitInt(s, str1_val, int1_val);
}

void TcpConnectClass::logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogitInt2(s, str1_val, int1_val, str2_val, int2_val);
}

void TcpConnectClass::abend (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangAbend(s, str1_val);
}

void TcpConnectClass::abend2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangAbend2(s, str1_val, str2_val);
}
