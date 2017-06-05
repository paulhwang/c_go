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
    void *theMainObject;
    void (*theReceiveCallbackFunc)(void *, void *);
    void *theAcceptCallbackParameter;

    pthread_t startServerThread(TpTransferClass *tp_transfer_val, unsigned short port_val,
                                            void (*accept_callback_func_val)(void *, void *),
                                            void *accept_callback_parameter_val,
                                            void (*receive_callback_func_val)(void *, void *),
                                            void *receive_callback_parameter_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
 
public:
    TpServerClass(void *main_object_val);
    ~TpServerClass(void);
    char const *objectName(void) {return "TpServerClass";}
    //void (*acceptCallbackFunc(void))(void *, void *) {return this->theAcceptCallbackFunc;}

    TpTransferClass *startServer(unsigned short port_val, void (*accept_callback_func_val)(void *, void *),
                                                          void *accept_callback_parameter_val,
                                                          void (*receive_callback_func_val)(void *, void *),
                                                          void *receive_callback_parameter_val,
                                                          StartServerOutputStruct *output_val);
    void serverThreadFunction(void *data_val);
};

typedef struct {
    unsigned long ip_addr;
    unsigned short port;
    TpServerClass *transport_object;
    TpTransferClass *tp_transfer_object;
    int socket;
    void (*accept_callback_func)(void *, void *);
    void *accept_callback_parameter;
    void (*receive_callback_func)(void *, void *);
    void *receive_callback_parameter;
} transport_thread_parameter;
