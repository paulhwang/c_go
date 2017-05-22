/*
  Copyrights reserved
  Written by Paul Hwang
  File name" go_move_class.h
*/

#ifndef __GO_MOVE_CLASS_H__
#define __GO_MOVE_CLASS_H__

#include "go_base_class.h"

class GoMoveClass {
public:
    GoMoveClass(GoBaseClass* base_object_val, char const* str_val, int x_val, int y_val, char color_val, int turn_val);
    GoMoveClass(GoBaseClass* base_object_val);
    ~GoMoveClass(void);

    char const* objectName(void);
    GoBaseClass* baseObject(void);

private:
    GoBaseClass *theBaseObject;

    int theX;
    int theY;
    char theMyColor;
    int theTurnIndex;

    int xX(void);
    int yY(void);
    char myColor(void);
    int turnIndex(void);

    void moveObjectDecode(char const* str_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
