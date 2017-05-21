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
    ~GoBoardClass(void);

    char const* objectName(void);
    GoBaseClass* baseObject(void);

    void resetMarkedBoardObjectData(void);
    char const* encodeBoard (void);

  private:
    GoBaseClass *theBaseObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
