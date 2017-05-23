/*
  Copyrights reserved
  Written by Paul Hwang
  File name: root_class.h
*/

#ifndef __GO_ROOT_CLASS_H__
#define __GO_ROOT_CLASS_H__

class BaseMgrClass;
//#include "go_base_dir/go_base_class.h"
class GoBaseClass;

class RootClass {
  public:
    RootClass(void);
    ~RootClass(void);

    char const* objectName(void);
    BaseMgrClass* baseMgrObject(void);
    GoBaseClass* goBaseObject(void);
    void startEngine(void);

  private:
    BaseMgrClass* theBaseMgrObject;
    GoBaseClass* theGoBaseObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
