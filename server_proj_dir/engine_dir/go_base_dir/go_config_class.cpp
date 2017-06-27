/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_config_class.cpp
*/

#include <stdio.h>
#include "go_base_class.h"
#include "go_config_class.h"

GoConfigClass::GoConfigClass (GoBaseClass *base_object_val):
    theBaseObject(base_object_val),
    theBoardSize(19),
    theHandicapPoint(0)
{
    this->debug(true, "GoConfigClass", "init");
}

void GoConfigClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseLogit(s, str1_val);
}

void GoConfigClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseAbend(s, str1_val);
}
