/*
  Copyrights reserved
  Written by Paul Hwang
  File name: net_root_class.cpp
*/

#include "../phwang.h"
#include "net_root_class.h"
#include "tp_dir/tp_transfer_class.h"
#include "tcp_dir/tcp_server_class.h"
#include "tcp_dir/tcp_connect_class.h"

NetRootClass::NetRootClass (int debug_code_val)
{
    memset(this, 0, sizeof (*this));
    this->theDebugCode = debug_code_val;
}

NetRootClass::~NetRootClass(void)
{
}

void *NetRootClass::mallocTpServer (
                        void *caller_object_val,
                        unsigned short port_val,
                        void (*accept_callback_func_val)(void *, void *),
                        void *accept_callback_parameter_val,
                        void (*receive_callback_func_val)(void *, void *, void *),
                        void *receive_callback_parameter_val,
                        char const *who_val)
{
    TcpServerClass *tp_server_object = new TcpServerClass(
                    caller_object_val,
                    port_val,
                    accept_callback_func_val,
                    accept_callback_parameter_val,
                    receive_callback_func_val,
                    receive_callback_parameter_val,
                    who_val);

    if (tp_server_object) {
        tp_server_object->startServerThread();
    }
    return tp_server_object;
}

void *NetRootClass::tpConnect (
                    unsigned long ip_addr_val, 
                    unsigned short port_val, 
                    void (*receive_callback_val)(void *, void *, void *), 
                    void *receive_object_val,
                    char const *who_val)
{
    TcpConnectClass *connect = new TcpConnectClass(who_val);
    void *result = connect->tcpConnect(ip_addr_val, port_val, receive_callback_val, receive_object_val, who_val);
    delete connect;
    return result;
}

void NetRootClass::freeTcpServer (void *tcp_server_object_val)
{
    if (!tcp_server_object_val) {
        phwangAbendS("NetRootClass::freeTcpServer", "null tp_server_object_val");
        return;
    }

    if (strcmp(((TcpServerClass *) tcp_server_object_val)->objectName(), "TcpServerClass")) {
        phwangAbendS("NetRootClass::freeTcpServer", "wrong object");
        return;
    }

    delete (TcpServerClass *) tcp_server_object_val;
}

void NetRootClass::freeTpTransfer (void *tp_transfer_object_val)
{
    if (!tp_transfer_object_val) {
        phwangAbendS("phwangFreeTpTransfer", "null tp_transfer_object_val");
        return;
    }

    if (strcmp(((TpTransferClass *) tp_transfer_object_val)->objectName(), "TpTransferClass")) {
        phwangAbendS("phwangFreeTpTransfer", "wrong object");
        return;
    }

    delete (TpTransferClass *) tp_transfer_object_val;
}

void NetRootClass::tpTransmit (void *tp_transfer_object_val, char *data_val)
{
    if (!tp_transfer_object_val) {
        phwangAbendS("NetRootClass::tpTransmit", "null tp_transfer_object_val");
        return;
    }

    if (strcmp(((TpTransferClass *) tp_transfer_object_val)->objectName(), "TpTransferClass")) {
        phwangAbendS("NetRootClass::tpTransmit", "wrong object");
        return;
    }

    ((TpTransferClass *) tp_transfer_object_val)->exportTransmitData(data_val);
}
