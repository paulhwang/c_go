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

class TcpServerClass {
    void *theCallerObject;
    unsigned short thePort;
    void (*theAcceptCallbackFunc)(void *, void *);
    void (*theReceiveCallbackFunc)(void *, void *, void *);
    void *theAcceptCallbackParameter;
    void *theReceiveCallbackParameter;
    char const *theWho;
    pthread_t theServerThread;
    int theTpTransferObjectIndex;

public:
    TcpServerClass(void *caller_object_val,
            unsigned short port_val,
            void (*accept_callback_func_val)(void *, void *),
            void *accept_callback_parameter_val,
            void (*receive_callback_func_val)(void *, void *, void *),
            void *receive_callback_parameter_val,
            char const *who_val);
    ~TcpServerClass(void);
    char const *objectName(void) {return "TcpServerClass";}

    void *serverThreadFunction(void *data_val);
    void startServerThread(void);
};
