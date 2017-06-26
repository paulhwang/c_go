/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "group_class.h"
#include "fabric_class.h"

GroupClass::GroupClass (void *list_mgr_object_val, FabricClass *fabric_object_val):
        ListEntryClass(list_mgr_object_val),
        theFabricObject(fabric_object_val)
{
    this->theSessionArrayMgr = phwangArrayMgrMalloc(this->objectName(), 'p', 10);
    this->theMaxSessionTableArrayIndex = 0;

    this->debug(true, "GroupClass", this->groupIdIndex());
}

GroupClass::~GroupClass (void)
{
    phwangArrayMgrFree(this->theSessionArrayMgr);
}

void GroupClass::insertSession (SessionClass *session_object_val)
{
    phwangArrayMgrInsertElement(this->theSessionArrayMgr, session_object_val);

    int i = 0;
    while (i < this->theMaxSessionTableArrayIndex) {
        if (!this->theSessionTableArray1[i]) {
            this->theSessionTableArray1[i] = session_object_val;
            return;
        }
        i++;
    }

    if (this->theMaxSessionTableArrayIndex < GROUP_CLASS_SESSION_ARRAY_SIZE) {
        this->theSessionTableArray1[this->theMaxSessionTableArrayIndex] = session_object_val;
        this->theMaxSessionTableArrayIndex++;
        return;
    }

    this->abend("insertSession", "table is full");
}

void GroupClass::removeSession (SessionClass *session_object_val)
{
    phwangArrayMgrRemoveElement(this->theSessionArrayMgr, session_object_val);

    int i = 0;
    while (i < GROUP_CLASS_SESSION_ARRAY_SIZE) {
        if (this->theSessionTableArray1[i] == session_object_val) {
            this->theSessionTableArray1[i] = 0;
            return;
        }
        i++;
    }
    this->abend("insertSession", "not found");
}

void GroupClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void GroupClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
