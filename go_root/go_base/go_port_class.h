/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_PORT_CLASS_H__
#define __GO_PORT_CLASS_H__

#include "go_base_class.h"

class GoPortClass {
  public:
    GoPortClass(GoBaseClass* base_object_val);
    ~GoPortClass();

    char const* objectName();
    GoBaseClass* baseObject();

  private:
    GoBaseClass *theBaseObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
