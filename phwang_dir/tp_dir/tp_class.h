/*
  Copyrights reserved
  Written by Paul Hwang
  File name: transport_class.h
*/

#pragma once
#include <pthread.h>

#define TRANSPORT_TRANSMIT_QUEUE_SIZE 1000

class QueueMgrClass;
class TpTransferClass;

typedef struct {
    pthread_t server_thread;
    TpTransferClass *tp_transfer_object;
} StartServerOutputStruct;

class TpClass {
    void *theMainObject;

    pthread_t startServerThread(TpTransferClass *tp_transfer_val, unsigned short port_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
 
public:
    TpClass(void *main_object_val);
    ~TpClass(void);
    char const *objectName(void) {return "TpClass";}

    TpTransferClass *startServer(unsigned short port_val, void (*receive_callback_val)(void *, void *), void *receive_object_val, StartServerOutputStruct *output_val);
    void serverThreadFunction(unsigned short port_val, TpTransferClass *tp_transfer_object_val);
};

typedef struct {
    unsigned long ip_addr;
    unsigned short port;
    TpClass *transport_object;
    TpTransferClass *tp_transfer_object;
    int socket;
} transport_thread_parameter;