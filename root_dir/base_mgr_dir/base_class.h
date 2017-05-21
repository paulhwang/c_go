/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_class.h
*/

#ifndef __BASE_CLASS_H__
#define __BASE_CLASS_H__

#include "base_mgr_class.h"

class BaseClass {
  public:
    BaseClass(BaseMgrClass* base_mgr_object_val);
    ~BaseClass();

    char const* objectName();
    BaseMgrClass* baseMgrObject();

    void receiveData(char* data_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  private:
  	BaseMgrClass* theBaseMgrObject;
};
#endif
