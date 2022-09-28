/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_config_class.cpp
*/

#include <stdio.h>
#include "../../define_dir/fe_def.h"
#include "go_base_class.h"
#include "go_config_class.h"

GoConfigClass::GoConfigClass (GoBaseClass *base_object_val, char *config_info_val):
    theBaseObject(base_object_val)
{
    if (*config_info_val != FE_DEF::FE_APP_IS_GO_GAME) {
        this->abend("GoConfigClass", "not GO");
    }
    this->debug(true, "GoConfigClass", config_info_val);

    char *current = config_info_val + 4;
    this->theBoardSize = phwangDecodeNumber(current, 2);
    current += 2;

    this->theHandicapPoint = phwangDecodeNumber(current, 2);
    current += 2;

    this->theKomi = phwangDecodeNumber(current, 2);
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
