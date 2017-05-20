/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_MOVE_CLASS_H__
#define __GO_MOVE_CLASS_H__

#include "go_base_class.h"

class GoMoveClass {
  public:
    GoMoveClass(GoBaseClass* base_object_val);
    ~GoMoveClass();

    char const* objectName();
    GoBaseClass* baseObject();

  private:
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
