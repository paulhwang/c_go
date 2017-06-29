/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../protocol_dir/base_mgr_protocol.h"
#include "engine_class.h"
#include "go_base_dir/go_base_class.h"
#include "d_engine_dir/d_engine_class.h"

EngineClass::EngineClass (void)
{
    memset(this, 0, sizeof(EngineClass));
    this->theDEngineObject = new DEngineClass(this);
    this->theGoBaseListMgrObject = phwangListMgrMalloc("GO_BASE", BASE_MGR_PROTOCOL_BASE_ID_SIZE, BASE_MGR_PROTOCOL_BASE_INDEX_SIZE, 900);

    this->debug(true, "EngineClass", "init");
}

EngineClass::~EngineClass (void)
{
    this->theDEngineObject->~DEngineClass();
}

GoBaseClass *EngineClass::mallocGoBase (char *config_info_val)
{
    this->debug(true, "mallocGoBase", "");
    GoBaseClass *base_object = new GoBaseClass(this->theGoBaseListMgrObject, this, config_info_val);
    return base_object;
}

void EngineClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void EngineClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
