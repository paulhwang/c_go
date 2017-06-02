/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.h
*/

#pragma once

#include <pthread.h>
class QueueMgrClass;
class EngineClass;
class BaseClass;
class GoBaseClass;

#include "base_mgr_protocol.h"
#include "../go_base_dir/go_base_class.h"

#define BASE_MGR_RECEIVE_QUEUE_SIZE 100

class BaseMgrClass {
#define BASE_MGR_BASE_ARRAY_SIZE 1000
#define BASE_MGR_MAX_GLOBAL_BASE_ID 9999

    void *theMainObject;
    int theGlobalBaseId;
    void *theBaseTableArray[BASE_MGR_BASE_ARRAY_SIZE + 4];

    pthread_t theReceiveThread;
    QueueMgrClass *theReceiveQueue;

    int allocBaseId(void);
    int allocBaseIndex(void);
    void mallocGoBase(void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    BaseMgrClass(void *main_object_val);
    ~BaseMgrClass();
    char const* objectName(void) {return "BaseMgrClass";}

    /* exports */
    void exportReceiveData(void *data_val);

    void startThreads(void);
    void receiveThreadFunction(void);
    void receiveThreadLoop(void);
    void receiveData(char* data_val);
    void transmitData(char *data_val);

    void baseMgrLogit(char const* str0_val, char const* str1_val);
    void baseMgrAbend(char const* str0_val, char const* str1_val);
};
