/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_move_class.cpp
*/

#include <stdio.h>
#include "go_base_class.h"
#include "go_move_class.h"

GoMoveClass::GoMoveClass (GoBaseClass *base_object_val, char const *encoded_move_val):
    theBaseObject(base_object_val)
{
    this->moveObjectDecode(encoded_move_val);
    this->debug(true, "GoMoveClass", this->theMoveInfo);
}

void GoMoveClass::moveObjectDecode (char const *str_val)
{
    this->debug(false, "moveObjectDecode", str_val);

    this->theX = (*str_val++ - '0') * 10;
    this->theX += (*str_val++ - '0');
    this->theY = (*str_val++ - '0') * 10;
    this->theY += (*str_val++ - '0');
    this->theMyColor = *str_val++;
    this->theTurnIndex = (*str_val++ - '0') * 100;
    this->theTurnIndex += (*str_val++ - '0') * 10;
    this->theTurnIndex += (*str_val - '0');

    sprintf(this->theMoveInfo, "(%i, %i) %c, %i", this->theX, this->theY, this->theMyColor, this->theTurnIndex);
}

void GoMoveClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseLogit(s, str1_val);
}

void GoMoveClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseAbend(s, str1_val);
}
