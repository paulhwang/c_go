/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.h
*/

#pragma once
#include <pthread.h>

#define TP_PHWANG_LOGO "phwang168"

class TpTransferClass {
public:
    const static int CLIENT_INDEX  = 0;
    const static int SERVER_INDEX  = 1;

private:
    const static int DATA_LENGTH_SIZE = 4;
    const static int RECEIVE_BUFFER_SIZE = 2048;
    const static int TRANSMIT_QUEUE_SIZE = 1024;
    const static int RECEIVE_QUEUE_SIZE  = 1024;

    static int ObjectCount;

    void (*theReceiveCallback)(void *, void *, void *);
    void *theReceiveObject;
    int theSocket;
    int theIndex;
    char const *theWho;
    char theWhoForReceiveQueue[64];
    char theWhoForTransmitQueue[64];
    int theMaxDataSize;

    pthread_t theReceiveThread;
    pthread_t theReceiveThread2;
    pthread_t theTransmitThread;
    void *theTransmitQueue;
    void *theReceiveQueue;

    void setMaxDataSize(void) {this->theMaxDataSize = 1; for (int i = 0; i < TpTransferClass::DATA_LENGTH_SIZE; i++) this->theMaxDataSize *= 10; this->theMaxDataSize -= 1;}
    void startReceiveThread(int socket_val);
    void startReceiveThread2(void);
    void startTransmitThread(int socket_val);

    int maxDataSize(void) {return this->theMaxDataSize;};

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
    void composeFuncNameExtra(char *buf_val, char const *func_name_val) {phwangComposeFuncNameExtra(buf_val, this->objectName(), func_name_val, this->theWho);}

public:
    TpTransferClass(int socket_val, void (*receive_callback_val)(void *, void *, void *), void *receive_object_val, char const *who_val);
    ~TpTransferClass(void);
    char const *objectName(void) {return "TpTransferClass";}
    static int objectCount(void);

    /* callback */
    void *receiveThreadFunction(int socket_val);
    void *receiveThreadFunction2(void);
    void *transmitThreadFunction(int socket_val);

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

