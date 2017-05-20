/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_BOARD_CLASS_H__
#define __GO_BOARD_CLASS_H__

#include "go_base_class.h"

class GoBoardClass {
  public:
    GoBoardClass(GoBaseClass* the_base_object);
    ~GoBoardClass();

    char const* objectName();
    GoBaseClass* baseObject();

    void resetMarkedBoardObjectData();

  private:
    GoBaseClass *theBaseObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
