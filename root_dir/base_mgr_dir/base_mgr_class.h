/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.h
*/

#ifndef __BASE_MGR_CLASS_H__
#define __BASE_MGR_CLASS_H__

class EngineClass;
class BaseClass;
class GoBaseClass;

#include "../../engine_class.h"

class BaseMgrClass {
  public:
    BaseMgrClass(EngineClass *engine_object_val);
    ~BaseMgrClass();

    char const* objectName();
    EngineClass* engineObject();

    void createBase(char const* base_name_val);
    void createGoBase(void);
    void receiveData(int base_id_val, char* data_val);

    void baseMgrLogit(char const* str0_val, char const* str1_val);
    void baseMgrAbend(char const* str0_val, char const* str1_val);

    GoBaseClass* goBaseObject(void);
    GoBaseClass* theGoBaseObject;

  private:
  	EngineClass* theEngineObject;

    BaseClass* getBase(int base_id_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
