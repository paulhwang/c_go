/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.h
*/

#pragma once
#include <pthread.h>

#define TP_TRANSFER_CLASS_TRANSMIT_QUEUE_SIZE 1000
#define TP_TRANSFER_CLASS_RECEIVE_BUFFER_SIZE 1024

class TpTransferClass {
    void (*theReceiveCallback)(void *, void *);
    void *theReceiveObject;
    int theSocket;

    pthread_t theReceiveThread;
    pthread_t theTransmitThread;
    void *theTransmitQueue;

    void startReceiveThread(int socket_val);
    void startTransmitThread(int socket_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    TpTransferClass(int socket_val, void (*receive_callback_val)(void *, void *), void *receive_object_val);
    ~TpTransferClass(void);
    char const *objectName(void) {return "TpTransferClass";}
    int socket(void) {return this->theSocket;}
    void (*receiveCallback(void))(void *, void *) {return this->theReceiveCallback;}

    /* exports */
    void exportTransmitData(void *data_val);
    void startThreads(void);

    /* callback */
    void receiveThreadFunction(int socket_val);
    void transmitThreadFunction(int socket_val);
};

typedef struct {
    TpTransferClass *tp_transfer_object;
    int socket;
} tp_transfer_thread_parameter;
