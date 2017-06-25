/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "base_mgr_class.h"
#include "../go_base_dir/go_base_class.h"

BaseMgrClass::BaseMgrClass (EngineClass *engine_object_val)
{
    memset(this, 0, sizeof(BaseMgrClass));
    this->theEngineObject = engine_object_val;
    this->theGlobalBaseId = 900;

    this->debug(true, "BaseMgrClass", "init");
}

BaseMgrClass::~BaseMgrClass (void)
{
}

int BaseMgrClass::allocBaseIndex (void)
{
    int index = 0;
    while (index < BASE_MGR_BASE_ARRAY_SIZE) {
        if (!this->theBaseTableArray[index]) {
            return index;
        }
        index++;
    }
    return -1;
}

int BaseMgrClass::allocBaseId (void)
{
    if (this->theGlobalBaseId >= BASE_MGR_MAX_GLOBAL_BASE_ID) {
        this->theGlobalBaseId = 0;
    }
    this->theGlobalBaseId++;
    return this->theGlobalBaseId;
}

GoBaseClass *BaseMgrClass::getBaseByIdIndex (int base_id_val, int base_index_val)
{
    if (base_id_val > BASE_MGR_MAX_GLOBAL_BASE_ID) {
        this->abend("getBaseByIdIndex", "base_id_val too big");
        return 0;
    }

    if (base_index_val >= BASE_MGR_BASE_ARRAY_SIZE) {
        this->abend("getBaseByIdIndex", "base_index_val too big");
        return 0;
    }

    GoBaseClass *base = this->theBaseTableArray[base_index_val];
    if (!base) {
        this->abend("getBaseByIdIndex", "null base");
        return 0;
    }

    if (base->baseId() != base_id_val){
        this->abend("getBaseByIdIndex", "base id does not match");
        return 0;
    }

    return base;
}

void BaseMgrClass::baseMgrLogit (char const* str0_val, char const* str1_val) {
    phwangLogit(str0_val, str1_val);
}

void BaseMgrClass::baseMgrAbend (char const* str0_val, char const* str1_val) {
    phwangAbend(str0_val, str1_val);
}

void BaseMgrClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseMgrLogit(s, str1_val);
}

void BaseMgrClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseMgrAbend(s, str1_val);
}

