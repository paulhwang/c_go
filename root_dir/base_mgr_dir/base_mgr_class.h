/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.h
*/

#ifndef __BASE_MGR_CLASS_H__
#define __BASE_MGR_CLASS_H__

class BaseClass;

#include "../root_class.h"
//#include "base_class.h"

class BaseMgrClass {
  public:
    BaseMgrClass(RootClass* root_object_val);
    ~BaseMgrClass();

    char const* objectName();
    RootClass* rootObject();

    void receiveData(int base_id_val, char* data_val);

    void baseMgrLogit(char const* str0_val, char const* str1_val);
    void baseMgrAbend(char const* str0_val, char const* str1_val);

  private:
  	RootClass* theRootObject;

    BaseClass* getBase(int base_id_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
