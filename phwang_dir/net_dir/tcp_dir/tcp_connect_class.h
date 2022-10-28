/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tcp_connect_class.h
*/

#pragma once

class TcpConnectClass {
    int debugOn_;
    char const *objectName(void) {return "TcpConnectClass";}
    char const *theWho;

public:
    TcpConnectClass(char const *who_val);
    ~TcpConnectClass(void);

    void *tcpConnect(unsigned long ip_addr_val, 
                     unsigned short port_val, 
                     void (*receive_callback_val)(void *, void *, void *), 
                     void *receive_object_val,
                     char const *who_val);
};
