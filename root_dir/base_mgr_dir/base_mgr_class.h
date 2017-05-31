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

class BaseMgrClass {
  	void *mainObject;
    pthread_t receiveThread;

    GoBaseClass *theTestGoBase;

    QueueMgrClass *receiveQueue;

    GoBaseClass* getBaseByBaseId(int base_id_val);
    int mallocBase(void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    BaseMgrClass(void *main_object_val);
    ~BaseMgrClass();

    void startThreads(void);
    char const* objectName(void) {return "BaseMgrClass";}

    /* exports */
    void exportReceiveData(void *data_val);

    void receiveThreadFunction(void);
    void receiveThreadLoop(void);
    void createBase(void);
    void receiveData(int base_id_val, char* data_val);
    void transmitData(char *data_val);

    void baseMgrLogit(char const* str0_val, char const* str1_val);
    void baseMgrAbend(char const* str0_val, char const* str1_val);

    GoBaseClass* goBaseObject(void);
    GoBaseClass* theGoBaseObject;
};
