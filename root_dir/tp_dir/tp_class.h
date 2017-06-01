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
class TpTransferClass;

class TpClass {
    void *theMainObject;

    QueueMgrClass *transmitQueue;

    pthread_t theServerThread;
    pthread_t theClientThread;
    pthread_t transmitThread;
    pthread_t receiveThread;
    TpTransferClass *theTpTransferObject;

    void startServerThread(TpTransferClass *tp_transfer_val, unsigned short port_val);
    void startClientThread(unsigned long ip_addr_val, unsigned short port_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
 
public:
    TpClass(void *main_object_val);
    ~TpClass(void);
    char const *objectName(void) {return "TpClass";}
    void *mainObject(void) {return this->theMainObject;}

    /* exports */
    void exportTransmitData1(void *data_val);

    TpTransferClass *startServer(unsigned short port_val);
    void serverThreadFunction(unsigned short port_val);
    TpTransferClass *clientThreadFunction(unsigned long ip_addr_val, unsigned short port_val);
};

typedef struct {
    unsigned long ip_addr;
    unsigned short port;
    TpClass *transport_object;
    int socket;
} transport_thread_parameter;

