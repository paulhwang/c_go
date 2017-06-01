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
class TpServerClass;

class TpClass {
    void *theMainObject;

    QueueMgrClass *transmitQueue;

    pthread_t serverThread;
    pthread_t clientThread;
    pthread_t transmitThread;
    pthread_t receiveThread;

    void startServerThread(TpServerClass *transport_server_val);
    void startClientThread(unsigned long ip_addr_val, unsigned short port_val);
    void startReceiveThread(int socket_val);
    void startTransmitThread(int socket_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
 
public:
    TpClass(void *main_object_val);
    ~TpClass(void);
    char const *objectName(void) {return "TpClass";}
    void *mainObject(void) {return this->theMainObject;}

    /* exports */
    void exportTransmitData(void *data_val);

    TpServerClass *startServer(unsigned short port_val);
    void serverThreadFunction(unsigned short port_val);
    void clientThreadFunction(unsigned long ip_addr_val, unsigned short port_val);
    void receiveThreadFunction(int socket_val);
    void transmitThreadFunction(int socket_val);
};

typedef struct {
    unsigned long ip_addr;
    unsigned short port;
    TpClass *transport_object;
    int socket;
} transport_thread_parameter;

