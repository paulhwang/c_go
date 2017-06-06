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

class TpServerClass {
    void *theCallerObject;
    unsigned short thePort;
    void (*theAcceptCallbackFunc)(void *, void *);
    void (*theReceiveCallbackFunc)(void *, void *);
    void *theAcceptCallbackParameter;
    void *theReceiveCallbackParameter;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
 
public:
    TpServerClass(void *caller_object_val,
            unsigned short port_val,
            void (*accept_callback_func_val)(void *, void *),
            void *accept_callback_parameter_val,
            void (*receive_callback_func_val)(void *, void *),
            void *receive_callback_parameter_val);
    ~TpServerClass(void);
    char const *objectName(void) {return "TpServerClass";}

    pthread_t startServerThread(void);
    void serverThreadFunction(void *data_val);
};

typedef struct {
    TpServerClass *tp_server_object;
    unsigned short port;
    void (*accept_callback_func)(void *, void *);
    void *accept_callback_parameter;
    void (*receive_callback_func)(void *, void *);
    void *receive_callback_parameter;
} tp_server_thread_parameter;
