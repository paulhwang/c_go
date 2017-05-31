/*
  Copyrights reserved
  Written by Paul Hwang
  File name: transport_server_class.h
*/

#pragma once

class TransportServerClass {
    void *transport_object;
    unsigned short thePort;

public:
    TransportServerClass(void *transport_object_val, unsigned short port_val);
    ~TransportServerClass(void);
    char const *objectName(void) {return "TransportServerClass";}

    unsigned short port(void) {return this->thePort;}
};
