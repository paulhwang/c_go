/*
  Copyrights reserved
  Written by Paul Hwang
*/


#pragma once
#include "../includes/common.h"

class TransportClass {
    void *mainObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
 
public:
    TransportClass(void *main_object_val);
    ~TransportClass();

    void startServerThread(ushort port_val);
    void startServer(ushort port_val);
    void startClient(ulong ip_addr_val, ushort port_val);
};
