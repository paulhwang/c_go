/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.h
*/

#pragma once

class QueueMgrClass;
class EngineClass;
class BaseClass;
class GoBaseClass;

#include "../../main_class.h"
#include "../go_base_dir/go_base_class.h"

#define BASE_MGR_RECEIVE_QUEUE_SIZE 100
#define BASE_ID_SIZE 4

class BaseMgrClass {
#define BASE_MGR_BASE_ARRAY_SIZE 1000
#define BASE_MGR_MAX_GLOBAL_BASE_ID 9999

    void *theMainObject;
    int theGlobalBaseId;
    int theBaseIndexArray[BASE_MGR_BASE_ARRAY_SIZE + 4];
    void *theBaseTableArray[BASE_MGR_BASE_ARRAY_SIZE + 4];

    pthread_t theReceiveThread;
    QueueMgrClass *theReceiveQueue;

    void *getBaseByBaseId(int base_id_val);
    int allocBaseId(void);
    int allocBaseIndex(void);
    void mallocBase(void);
    void encodeBaseId(int base_id_val, char *buf_val);
    int decodeBaseId(char *data_val);

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
    void createBase(void);
    void receiveData(char* data_val);
    void transmitData(char *data_val);

    void baseMgrLogit(char const* str0_val, char const* str1_val);
    void baseMgrAbend(char const* str0_val, char const* str1_val);

    GoBaseClass* goBaseObject(void);
    GoBaseClass* theGoBaseObject;
};
