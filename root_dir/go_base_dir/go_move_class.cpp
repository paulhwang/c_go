/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_move_class.cpp
*/

#include "../root_common.h"
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

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "new move created: (%i, %s, %i, %i)", this->xX(), this->yY(), this->myColor(), this->turnIndex());
        this->logit("init", s);
    }
}

GoMoveClass::GoMoveClass (GoBaseClass* base_object_val)
{
    this->theBaseObject = base_object_val;

    if (1) {
      this->logit("init", "");
    }
}

GoMoveClass::~GoMoveClass (void)
{
}

char const* GoMoveClass::objectName (void)
{
    return "GoMoveClass";
}

GoBaseClass* GoMoveClass::baseObject (void)
{
    return this->theBaseObject;
}

int GoMoveClass::xX (void)
{

}

int GoMoveClass::yY (void)
{

}

char GoMoveClass::myColor (void)
{

}

int GoMoveClass::turnIndex (void)
{

}

void GoMoveClass::moveObjectDecode (char const* str_val)
{

}

void GoMoveClass::logit (char const* str0_val,
                         char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseObject()->goBaseLogit(s, str1_val);
}

void GoMoveClass::abend (char const* str0_val,
                         char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseObject()->goBaseAbend(s, str1_val);
}



