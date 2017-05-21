/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.h
*/

#ifndef __BASE_MGR_CLASS_H__
#define __BASE_MGR_CLASS_H__

#include "../root_class.h"

class BaseMgrClass {
  public:
    BaseMgrClass(RootClass* root_object_val);
    ~BaseMgrClass();

    char const* objectName();
    RootClass* rootObject();

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  private:
  	RootClass* theRootObject;
};
#endif
