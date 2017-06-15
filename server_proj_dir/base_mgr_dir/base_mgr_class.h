/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.h
*/

#pragma once

#include <pthread.h>
#include "../protocol_dir/base_mgr_protocol.h"
#include "go_base_dir/go_base_class.h"
class BaseClass;
class GoBaseClass;

#define BASE_MGR_RECEIVE_QUEUE_SIZE 100

class BaseMgrClass {
#define BASE_MGR_BASE_ARRAY_SIZE 1000
#define BASE_MGR_MAX_GLOBAL_BASE_ID 9999

    void *theMainObject;
    void *theTpServerObject;
    int theGlobalBaseId;
    void *theBaseTableArray[BASE_MGR_BASE_ARRAY_SIZE + 4];

    void *theTpTransferObject;
    pthread_t theTpServerThread;
    pthread_t theReceiveThread;
    void *theReceiveQueue;

    void startReceiveThread(void);
    void receiveFunction(char *data_val);

    int allocBaseId(void);
    int allocBaseIndex(void);
    void mallocGoBase(void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    BaseMgrClass(void *main_object_val);
    ~BaseMgrClass();
    char const* objectName(void) {return "BaseMgrClass";}
    pthread_t receiveThread(void) {return this->theReceiveThread;}

    /* exports */
    void exportedReceiveFunction(void *data_val);
    void exportedAcceptFunction(void *tp_transfer_object_val);

    void startThreads(void);
    void startNetServer(void);
    void startNetConnect(void);
    void receiveThreadFunction(void);
    void receiveData(char* data_val);
    void transmitFunction(char *data_val);

    void baseMgrLogit(char const* str0_val, char const* str1_val);
    void baseMgrAbend(char const* str0_val, char const* str1_val);
};
