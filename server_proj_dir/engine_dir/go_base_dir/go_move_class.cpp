/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_move_class.cpp
*/

#include <stdio.h>
#include "go_base_class.h"
#include "go_move_class.h"

GoMoveClass::GoMoveClass (GoBaseClass* base_object_val,
                         char const* str_val,
                         int x_val,
                         int y_val,
                         char color_val,
                         int turn_val)
{
    this->theBaseObject = base_object_val;
    if (!str_val) {
        this->theX = x_val;
        this->theY = y_val;
        this->theMyColor = color_val;
        this->theTurnIndex = turn_val;
    } else {
        this->moveObjectDecode(str_val);
    }

    if (0) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "new move created: (%i, %i, %i, %i)", this->xX(), this->yY(), this->myColor(), this->turnIndex());
        this->logit("init", s);
    }
}

void GoMoveClass::moveObjectDecode (char const* str_val)
{
    this->debug(true, "moveObjectDecode", str_val);

    this->theX = (*str_val++ - '0') * 10;
    this->theX += (*str_val++ - '0');
    this->theY = (*str_val++ - '0') * 10;
    this->theY += (*str_val++ - '0');
    this->theMyColor = *str_val++;
    this->theTurnIndex = (*str_val++ - '0') * 100;
    this->theTurnIndex += (*str_val++ - '0') * 10;
    this->theTurnIndex += (*str_val - '0');
}

void GoMoveClass::logit (char const* str0_val,
                         char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseLogit(s, str1_val);
}

void GoMoveClass::abend (char const* str0_val,
                         char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseAbend(s, str1_val);
}
