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
    pthread_t clientThread;
    pthread_t transmitThread;
    pthread_t receiveThread;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
 
public:
    TransportClass(void *main_object_val);
    ~TransportClass();

    void startServerThread(ushort port_val);
    void serverThreadFunction(ushort port_val);
    void startClientThread(unsigned long ip_addr_val, ushort port_val);
    void clientThreadFunction(unsigned long ip_addr_val, ushort port_val);
    void startReceiveThread(int socket_val);
    void ReceiveThreadFunction(int socket_val);
    void startTransmitThread(int socket_val);
    void transmitThreadFunction(int socket_val);
    char const *objectName(void) {return "TransportClass";}
};

typedef struct {
    unsigned long ip_addr;
    unsigned short port;
    TransportClass *transport_object;
    int socket;
} transport_thread_parameter;

