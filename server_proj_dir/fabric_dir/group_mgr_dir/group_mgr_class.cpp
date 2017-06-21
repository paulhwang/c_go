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
    this->theGlobalGroupId = 500;

    this->debug(true, "GroupMgrClass", "init");
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

GroupClass *GroupMgrClass::searchGroup (char *data_val)
{
    int group_id;
    int group_index;

    this->debug(true, "searchGroup", data_val);

    phwangDecodeIdIndex(data_val,
                &group_id,
                GROUP_MGR_PROTOCOL_GROUP_ID_SIZE,
                &group_index,
                GROUP_MGR_PROTOCOL_GROUP_INDEX_SIZE);

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "group_id=%d group_index=%d", group_id, group_index);
        this->logit("searchGroup", s);
    }

    return this->getGroupByIdIndex(group_id, group_index);
}

GroupClass *GroupMgrClass::getGroupByIdIndex (int group_id_val, int group_index_val)
{
    if (group_id_val > GROUP_MGR_MAX_GLOBAL_GROUP_ID) {
        this->abend("getSessionByIdIndex", "group_id_val too big");
        return 0;
    }

    if (group_index_val >= GROUP_MGR_GROUP_ARRAY_SIZE) {
        this->abend("getSessionByIdIndex", "group_index_val too big");
        return 0;
    }

    GroupClass *group = this->theGroupTableArray[group_index_val];
    if (!group) {
        this->abend("getLinkByIdIndex", "null group");
        return 0;
    }

    if (group->groupId() != group_id_val){
        this->abend("getLinkByIdIndex", "group id does not match");
        return 0;
    }

    return group;
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

