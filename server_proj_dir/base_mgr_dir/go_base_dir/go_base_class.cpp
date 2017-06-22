/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../base_mgr_class.h"
#include "go_base_class.h"

GoBaseClass::GoBaseClass (BaseMgrClass* base_mgr_object_val, int base_id_val, int base_index_val)
{
    this->theBaseId = base_id_val;
    this->theBaseIndex = base_index_val;
    phwangEncodeIdIndex(this->theBaseIdIndex, this->theBaseId, BASE_MGR_PROTOCOL_BASE_ID_SIZE, this->theBaseIndex, BASE_MGR_PROTOCOL_BASE_INDEX_SIZE);

    this->theBaseMgrObject = base_mgr_object_val;
    this->theConfigObject = new GoConfigClass(this);
    this->theBoardObject = new GoBoardClass(this);
    this->theEngineObject = new GoEngineClass(this);
    this->thePortObject = new GoPortClass(this);
    this->theGameObject = new GoGameClass(this);

    this->debug(true, "GoBaseClass", this->theBaseIdIndex);
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


