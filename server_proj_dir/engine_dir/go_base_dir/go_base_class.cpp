/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "go_base_class.h"
#include "../engine_class.h"

GoBaseClass::GoBaseClass (void* list_mgr_object_val, EngineClass *engine_object_val):
        ListEntryClass(list_mgr_object_val),
        theEngineObject___(engine_object_val)
{
    this->theConfigObject = new GoConfigClass(this);
    this->theBoardObject = new GoBoardClass(this);
    this->theEngineObject = new GoEngineClass(this);
    this->thePortObject = new GoPortClass(this);
    this->theGameObject = new GoGameClass(this);

    this->debug(true, "GoBaseClass", this->goBaseIdIndex());
}

GoBaseClass::~GoBaseClass (void)
{
}

void GoBaseClass::logit (char const* str0_val, char const* str1_val)
{
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->goBaseLogit(s, str1_val);
}

void GoBaseClass::abend (char const* str0_val, char const* str1_val)
{
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->goBaseAbend(s, str1_val);
}


