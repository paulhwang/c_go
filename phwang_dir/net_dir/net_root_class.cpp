/*
  Copyrights reserved
  Written by Paul Hwang
  File name: net_root_class.cpp
*/

#include "../phwang.h"
#include "net_root_class.h"
#include "port_dir/port_class.h"
#include "tcp_dir/tcp_server_class.h"
#include "tcp_dir/tcp_connect_class.h"
#include "ip_dir/ip_class.h"

NetRootClass::NetRootClass (int debug_code_val)
{
    memset(this, 0, sizeof (*this));
    this->debugOn_ = false;
    this->theIpObject = new IpClass();
    unsigned long ip_addr_ptr_val;
    this->theIpObject->getIpAddr(&ip_addr_ptr_val);
    this->theDebugCode = debug_code_val;
}

NetRootClass::~NetRootClass(void)
{
}

void *NetRootClass::mallocTpServer (
        int debug_on_val,
        void *caller_object_val,
        unsigned short port_val,
        void (*accept_callback_func_val)(void *, void *),
        void *accept_callback_parameter_val,
        void (*receive_callback_func_val)(void *, void *, void *),
        void *receive_callback_parameter_val,
        char const *who_val)
{
    TcpServerClass *tp_server_object = new TcpServerClass(
        debug_on_val,
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
        int debug_on_val,
        unsigned long ip_addr_val, 
        unsigned short port_val, 
        void (*receive_callback_val)(void *, void *, void *), 
        void *receive_object_val,
        char const *who_val)
{
    TcpConnectClass *connect = new TcpConnectClass(who_val);
    void *result = connect->tcpConnect(
        debug_on_val,
        ip_addr_val,
        port_val, 
        receive_callback_val,
        receive_object_val,
        who_val);
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

void NetRootClass::freePort (void *port_object_val)
{
    if (!port_object_val) {
        phwangAbendS("NetRootClass::freePort", "null port_object_val");
        return;
    }

    if (strcmp(((PortClass *) port_object_val)->objectName(), "TpTransferClass")) {
        phwangAbendS("NetRootClass::freePort", "wrong object");
        return;
    }

    delete (PortClass *) port_object_val;
}

void NetRootClass::portTransmit (void *port_object_val, char *data_val)
{
    if (!port_object_val) {
        phwangAbendS("NetRootClass::portTransmit", "null port_object_val");
        return;
    }

    if (!data_val) {
        phwangAbendS("NetRootClass::portTransmit", "null data_val");
        return;
    }

    if (strcmp(((PortClass *) port_object_val)->objectName(), "PortClass")) {
        phwangAbendS("NetRootClass::portTransmit", "wrong object");
        return;
    }

    ((PortClass *) port_object_val)->exportTransmitData(data_val);
}

int NetRootClass::getPortObjectIndex (void *port_object_val)
{
    if (!port_object_val) {
        phwangAbendS("NetRootClass::getPortObjectIndex", "null port_object_val");
        return 0;
    }

    return ((PortClass *) port_object_val)->index();
}
