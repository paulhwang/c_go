/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_server_class.h
*/

#pragma once

class TpServerClass {
    void *transport_object;
    unsigned short thePort;

public:
    TpServerClass(void *transport_object_val, unsigned short port_val);
    ~TpServerClass(void);
    char const *objectName(void) {return "TpServerClass";}

    unsigned short port(void) {return this->thePort;}
};
