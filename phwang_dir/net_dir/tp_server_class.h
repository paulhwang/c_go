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
    void (*theReceiveCallbackFunc)(void *, void *, void *);
    void *theAcceptCallbackParameter;
    void *theReceiveCallbackParameter;
    char const *theWho;
    pthread_t theServerThread;
    int theTpTransferObjectIndex;

    void debug(int debug_on_val, char const *func_name_val, char const *str1_val);
    void debug2(int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val);
    void debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val);
    void debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void logit(char const *func_name_val, char const *str1_val);
    void logit2(char const *func_name_val, char const *str1_val, char const *str2_val);
    void logitInt(char const *func_name_val, char const *str1_val, int int1_val);
    void logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void abend(char const *func_name_val, char const *str1_val);
    void abend2(char const *func_name_val, char const *str1_val, char const *str2_val);

public:
    TpServerClass(void *caller_object_val,
            unsigned short port_val,
            void (*accept_callback_func_val)(void *, void *),
            void *accept_callback_parameter_val,
            void (*receive_callback_func_val)(void *, void *, void *),
            void *receive_callback_parameter_val,
            char const *who_val);
    ~TpServerClass(void);
    char const *objectName(void) {return "TpServerClass";}

    void *serverThreadFunction(void *data_val);
    void startServerThread(void);
};
