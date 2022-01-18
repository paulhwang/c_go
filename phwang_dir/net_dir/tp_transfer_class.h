/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.h
*/

#pragma once
#include <pthread.h>

#define TP_TRANSFER_CLASS_TRANSMIT_QUEUE_SIZE 1000
#define TP_TRANSFER_CLASS_RECEIVE_QUEUE_SIZE 1000
#define TP_TRANSFER_CLASS_RECEIVE_BUFFER_SIZE 1024

class TpTransferClass {
    void (*theReceiveCallback)(void *, void *, void *);
    void *theReceiveObject;
    int theSocket;
    int theIndex;
    char const *theWho;

    pthread_t theReceiveThread;
    pthread_t theReceiveThread2;
    pthread_t theTransmitThread;
    void *theTransmitQueue;
    void *theReceiveQueue;

    void startReceiveThread(int socket_val);
    void startReceiveThread2(void);
    void startTransmitThread(int socket_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    TpTransferClass(int socket_val, void (*receive_callback_val)(void *, void *, void *), void *receive_object_val, char const *who_val);
    ~TpTransferClass(void);
    char const *objectName(void) {return "TpTransferClass";}

    /* callback */
    void receiveThreadFunction(int socket_val);
    void receiveThreadFunction2(void);
    void transmitThreadFunction(int socket_val);

    int socket(void) {return this->theSocket;}
    int index(void) {return this->theIndex;}
    void (*receiveCallback(void))(void *, void *, void *) {return this->theReceiveCallback;}

    /* exports */
    void exportTransmitData(void *data_val);
    void startThreads(int index_val);
};

typedef struct {
    TpTransferClass *tp_transfer_object;
    int socket;
} tp_transfer_thread_parameter;

