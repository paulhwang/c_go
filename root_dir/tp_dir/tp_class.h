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

    pthread_t theServerThread;
    //pthread_t theClientThread;

    void startServerThread(TpTransferClass *tp_transfer_val, unsigned short port_val);
    //void startClientThread(unsigned long ip_addr_val, unsigned short port_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
 
public:
    TpClass(void *main_object_val);
    ~TpClass(void);
    char const *objectName(void) {return "TpClass";}
    void *mainObject(void) {return this->theMainObject;}

    TpTransferClass *startServer(unsigned short port_val, void (*receive_callback_val)(void *, void *));
    void serverThreadFunction(unsigned short port_val, TpTransferClass *tp_transfer_object_val);
    TpTransferClass *clientThreadFunction(unsigned long ip_addr_val, unsigned short port_val, void (*receive_callback_val)(void *, void *));
};

typedef struct {
    unsigned long ip_addr;
    unsigned short port;
    TpClass *transport_object;
    TpTransferClass *tp_transfer_object;
    int socket;
} transport_thread_parameter;

