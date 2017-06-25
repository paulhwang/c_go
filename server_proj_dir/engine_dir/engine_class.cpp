/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "engine_class.h"
#include "base_mgr_dir/base_mgr_class.h"
#include "go_base_dir/go_base_class.h"
#include "d_engine_dir/d_engine_class.h"

EngineClass::EngineClass (void)
{
    memset(this, 0, sizeof(EngineClass));
    this->theDEngineObject = new DEngineClass(this);
    this->theGoBaseMgrObject = new BaseMgrClass(this);
    this->theGoBaseListMgrObject = phwangMallocListMgr("GO_BASE", BASE_MGR_PROTOCOL_BASE_ID_SIZE, BASE_MGR_PROTOCOL_BASE_INDEX_SIZE, 900);

    this->debug(true, "EngineClass", "init");
}

EngineClass::~EngineClass (void)
{
    this->theGoBaseMgrObject->~BaseMgrClass(); 
    this->theDEngineObject->~DEngineClass();
}

GoBaseClass *EngineClass::mallocGoBase (void)
{
    int base_id = this->theGoBaseMgrObject->allocBaseId();
    int base_index = this->theGoBaseMgrObject->allocBaseIndex();
    if (base_index == -1) {
        this->abend("mallocGoBase", "no space");
        return 0;
    }

    GoBaseClass *base_object = new GoBaseClass(this->theGoBaseMgrObject, this, base_id, base_index);
    this->theGoBaseMgrObject->theBaseTableArray[base_index] = base_object;

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
