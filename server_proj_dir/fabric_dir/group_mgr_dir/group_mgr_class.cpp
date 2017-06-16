/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_mgr_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "group_mgr_class.h"
#include "group_class.h"

GroupMgrClass::GroupMgrClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(GroupMgrClass));
    this->theFabricObject = fabric_object_val;
    this->theGlobalGroupId = 0;

    if (1) {
        this->logit("GroupMgrClass", "init");
    }
}

GroupMgrClass::~GroupMgrClass (void)
{
}

int GroupMgrClass::allocGroupId (void)
{
    if (this->theGlobalGroupId >= GROUP_MGR_MAX_GLOBAL_GROUP_ID) {
        this->theGlobalGroupId = 0;
    }
    this->theGlobalGroupId++;
    return this->theGlobalGroupId;
}

int GroupMgrClass::allocGroupIndex (void)
{
    int index = 0;
    while (index < GROUP_MGR_GROUP_ARRAY_SIZE) {
        if (!this->theGroupTableArray[index]) {
            return index;
        }
        index++;
    }
    return -1;
}

GroupClass *GroupMgrClass::mallocGroup (void)
{
    if (1) {
        this->logit("mallocGroup", "");
    }
    int group_id = this->allocGroupId();
    int group_index = this->allocGroupIndex();
    if (group_index != -1) {
        GroupClass *group = new GroupClass(this, group_id, group_index);
        this->theGroupTableArray[group_index] = group;
        return group;
    }
    else {
        /* TBD */
    }
}

void GroupMgrClass::groupMgrLogit (char const* str0_val, char const* str1_val) {
    phwangLogit(str0_val, str1_val);
}

void GroupMgrClass::groupMgrAbend (char const* str0_val, char const* str1_val) {
    phwangAbend(str0_val, str1_val);
}

void GroupMgrClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->groupMgrLogit(s, str1_val);
}

void GroupMgrClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->groupMgrAbend(s, str1_val);
}

