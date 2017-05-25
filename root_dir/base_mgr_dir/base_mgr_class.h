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

class BaseMgrClass {
  	EngineClass* theEngineObject;

    GoBaseClass *theTestGoBase;

    GoBaseClass* getBaseByBaseId(int base_id_val);

    QueueMgrClass *goReceiveQueue(void) {return engineObject()->goReceiveQueue();}

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    BaseMgrClass(EngineClass *engine_object_val);
    ~BaseMgrClass();

    char const* objectName(void) {return "BaseMgrClass";}
    EngineClass* engineObject(void) {return theEngineObject;}

    void receiveThreadLoop(void);
    void createBase(void);
    void receiveData(int base_id_val, char* data_val);

    void baseMgrLogit(char const* str0_val, char const* str1_val);
    void baseMgrAbend(char const* str0_val, char const* str1_val);

    GoBaseClass* goBaseObject(void);
    GoBaseClass* theGoBaseObject;
};
#endif
