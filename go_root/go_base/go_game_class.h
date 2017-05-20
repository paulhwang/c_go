/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_GAME_CLASS_H__
#define __GO_GAME_CLASS_H__

#include "go_base_class.h"

class GoGameClass {
  public:
    GoGameClass(GoBaseClass* the_base_object);
    ~GoGameClass();

    char const* objectName();
    GoBaseClass* baseObject();

  private:
    GoBaseClass *theBaseObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
