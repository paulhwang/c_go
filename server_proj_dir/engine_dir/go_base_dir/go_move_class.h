/*
  Copyrights reserved
  Written by Paul Hwang
  File name" go_move_class.h
*/

#pragma once
#include "go_base_class.h"

class GoMoveClass {
    GoBaseClass *theBaseObject;
    int theX;
    int theY;
    char theMyColor;
    int theTurnIndex;

    void moveObjectDecode(char const *str_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    GoMoveClass(GoBaseClass *base_object_val, char const *str_val, int x_val, int y_val, char color_val, int turn_val);
    ~GoMoveClass(void) {}
    char const* objectName(void) {return "GoMoveClass";}

    int xX(void) {return this->theX;}
    int yY(void) {return this->theY;}
    char myColor(void) {return this->theMyColor;}
    int turnIndex(void) {return this->theTurnIndex;}
};
