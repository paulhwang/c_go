/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.h
*/

#ifndef __BASE_MGR_CLASS_H__
#define __BASE_MGR_CLASS_H__

class QueueMgrClass;
class EngineClass;
class BaseClass;
class GoBaseClass;

#include "../../engine_class.h"
#include "../go_base_dir/go_base_class.h"

#define BASE_MGR_RECEIVE_QUEUE_SIZE 100

class BaseMgrClass {
  	EngineClass* theEngineObject;

    GoBaseClass *theTestGoBase;

    QueueMgrClass *receiveQueue;

    GoBaseClass* getBaseByBaseId(int base_id_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    BaseMgrClass(EngineClass *engine_object_val);
    ~BaseMgrClass();

    char const* objectName(void) {return "BaseMgrClass";}
    EngineClass* engineObject(void) {return theEngineObject;}

    /* exports */
    void exportReceiveData(void *data_val);

    void receiveThreadLoop(void);
    void createBase(void);
    void receiveData(int base_id_val, char* data_val);
    void transmitData(char *data_val);

    void baseMgrLogit(char const* str0_val, char const* str1_val);
    void baseMgrAbend(char const* str0_val, char const* str1_val);

    GoBaseClass* goBaseObject(void);
    GoBaseClass* theGoBaseObject;
};
#endif
