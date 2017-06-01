/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.h
*/

#pragma once
#include <pthread.h>

class QueueMgrClass;
class TpClass;

class TpTransferClass {
    TpClass *tp_object;
    int theSocket;

    QueueMgrClass *transmitQueue;
    pthread_t transmitThread;
    pthread_t receiveThread;

    void startReceiveThread(int socket_val);
    void startTransmitThread(int socket_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    TpTransferClass(TpClass *tp_object_val, int socket_val);
    ~TpTransferClass(void);
    char const *objectName(void) {return "TpTransferClass";}

    /* exports */
    void exportTransmitData(void *data_val);

    int socket(void) {return this->theSocket;}
    void receiveThreadFunction(int socket_val);
    void transmitThreadFunction(int socket_val);
};

typedef struct {
    //unsigned long ip_addr;
    //unsigned short port;
    TpTransferClass *tp_transfer_object;
    int socket;
} tp_transfer_thread_parameter;

