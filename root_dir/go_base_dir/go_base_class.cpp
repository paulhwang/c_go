/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.cpp
*/

#include <stdio.h>
#include "../../utils_dir/logit.h"
#include "../base_mgr_dir/base_mgr_class.h"
#include "go_base_class.h"

GoBaseClass::GoBaseClass (BaseMgrClass* base_mgr_object_val, int base_id_val)
{
  this->theBaseId = base_id_val;
  this->theBaseMgrObject = base_mgr_object_val;
  this->theConfigObject = new GoConfigClass(this);
  this->theBoardObject = new GoBoardClass(this);
  this->theEngineObject = new GoEngineClass(this);
  this->thePortObject = new GoPortClass(this);
  this->theGameObject = new GoGameClass(this);

  if (1) {
    this->logit("GoBaseClass", "init");
  }
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


