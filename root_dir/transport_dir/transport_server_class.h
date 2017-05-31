/*
  Copyrights reserved
  Written by Paul Hwang
  File name: transport_server_class.h
*/

#pragma once

class TransportServerClass {

public:
    TransportServerClass(void *main_object_val);
    ~TransportServerClass(void);
    char const *objectName(void) {return "TransportServerClass";}
};
