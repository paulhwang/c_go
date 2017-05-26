/*
  Copyrights reserved
  Written by Paul Hwang
*/


#pragma once
#include <pthread.h>
#include "../includes/common.h"

class TransportClass {
    void *mainObject;

    pthread_t serverThread;
    pthread_t transmitThread;
    pthread_t receiveThread;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
 
public:
    TransportClass(void *main_object_val);
    ~TransportClass();

    void startServerThread(ushort port_val);
    void serverThreadFunction(ushort port_val);
    void startClient(ulong ip_addr_val, ushort port_val);
    char const *objectName(void) {return "TransportClass";}
};

typedef struct {
    unsigned short port;
    TransportClass *transport_object;
} transport_server_thread_parameter;

