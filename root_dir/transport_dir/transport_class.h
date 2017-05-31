/*
  Copyrights reserved
  Written by Paul Hwang
  File name: transport_class.h
*/

#pragma once
#include <pthread.h>
#include "../../includes/common.h"

#define TRANSPORT_PORT_NUMBER_FOR_BASE_MGR 8003
#define TRANSPORT_PORT_NUMBER_FOR_LINK_MGR 8004
#define TRANSPORT_TRANSMIT_QUEUE_SIZE 1000

class QueueMgrClass;

class TransportClass {
    void *mainObject;

    QueueMgrClass *transmitQueue;

    pthread_t serverThread;
    pthread_t clientThread;
    pthread_t transmitThread;
    pthread_t receiveThread;

    void startServerThread(ushort port_val);
    void startClientThread(unsigned long ip_addr_val, ushort port_val);
    void startReceiveThread(int socket_val);
    void startTransmitThread(int socket_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
 
public:
    TransportClass(void *main_object_val);
    ~TransportClass(void);

    void startServer(ushort port_val);
    void serverThreadFunction(ushort port_val);
    void clientThreadFunction(unsigned long ip_addr_val, ushort port_val);
    void receiveThreadFunction(int socket_val);
    void transmitThreadFunction(int socket_val);

    /* exports */
    void exportTransmitData(void *data_val);

    char const *objectName(void) {return "TransportClass";}
};

typedef struct {
    unsigned long ip_addr;
    unsigned short port;
    TransportClass *transport_object;
    int socket;
} transport_thread_parameter;

