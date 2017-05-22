/*
  Copyrights reserved
  Written by Paul Hwang
  File name:go_config_class.h
*/

#ifndef __GO_BOARD_CLASS_H__
#define __GO_BOARD_CLASS_H__

class GoConfigClass;
//#include "go_config_class.h"
#include "go_base_class.h"

class GoBoardClass {
public:
    GoBoardClass(GoBaseClass* the_base_object);
    ~GoBoardClass(void);

    char const* objectName(void);
    GoBaseClass* baseObject(void);

    void resetMarkedBoardObjectData(void);
    void encodeBoard(char* buf_ptr);

private:
    GoBaseClass *theBaseObject;
    GoConfigClass* configObject(void);

    int theBoardArray[19][19];
    int theMarkedBoardArray[19][19];

    int boardSize (void);

    void resetBoardObjectData (void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
