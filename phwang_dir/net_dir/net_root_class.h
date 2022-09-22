/*
  Copyrights reserved
  Written by Paul Hwang
  File name: net_root_class.h
*/

#pragma once

class IpClass;

class NetRootClass
{
    char const *objectName(void) {return "NetRootClass";}
    IpClass *theIpObject;
    int theDebugCode;
    int theReceiveThreadCount;

public:
    NetRootClass(int debug_code_val);
    ~NetRootClass(void);
    
    void *mallocTpServer (
            void *caller_object_val,
            unsigned short port_val,
            void (*accept_callback_func_val)(void *, void *),
            void *accept_callback_parameter_val,
            void (*receive_callback_func_val)(void *, void *, void *),
            void *receive_callback_parameter_val,
            char const *who_val);
    void *tpConnect(
            unsigned long ip_addr_val, 
            unsigned short port_val, 
            void (*receive_callback_val)(void *, void *, void *), 
            void *receive_object_val,
            char const *who_val);
    void freeTcpServer(void *tcp_server_object_val);
    void freeTpTransfer(void *tp_transfer_object_val);
    void tpTransmit(void *tp_transfer_object_val, char *data_val);
    int getPortObjectIndex(void *port_object_val);
    int receiveThreadCount(void) {return this->theReceiveThreadCount;}
    void incrementReceiveThreadCount(void) {this->theReceiveThreadCount++;}
};
