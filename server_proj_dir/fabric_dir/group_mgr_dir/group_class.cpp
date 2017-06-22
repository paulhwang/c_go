/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "group_class.h"
#include "group_mgr_class.h"

GroupClass::GroupClass (GroupMgrClass *group_mgr_object_val, int group_id_val, int group_index_val)
{
    memset(this, 0, sizeof(GroupClass));
    this->theGroupMgrObject = group_mgr_object_val;
    this->theGroupId = group_id_val;
    this->theGroupIndex = group_index_val;
    phwangEncodeIdIndex(this->theGroupIdIndex, this->theGroupId, GROUP_MGR_PROTOCOL_GROUP_ID_SIZE, this->theGroupIndex, GROUP_MGR_PROTOCOL_GROUP_INDEX_SIZE);

    this->theSessionListMgr = new ListMgrClass(this, SESSION_MGR_PROTOCOL_SESSION_ID_SIZE, SESSION_MGR_PROTOCOL_SESSION_INDEX_SIZE);

    this->debug(true, "GroupClass", this->theGroupIdIndex);
}

GroupClass::~GroupClass (void)
{
}

void GroupClass::insertSession (SessionClass *session_object_val)
{
    int i = 0;
    while (i < GROUP_SESSION_ARRAY_SIZE) {
        if (!this->theSessionTableArray[i]) {
            this->theSessionTableArray[i] = session_object_val;
            return;
        }
        i++;
    }
    this->abend("insertSession", "table is full");
}

void GroupClass::removeSession (SessionClass *session_object_val)
{
    int i = 0;
    while (i < GROUP_SESSION_ARRAY_SIZE) {
        if (this->theSessionTableArray[i] == session_object_val) {
            this->theSessionTableArray[i] = 0;
            return;
        }
        i++;
    }
    this->abend("insertSession", "not found");
}

void GroupClass::transmitToTheme(void *data_val, void *session_object_val)
{
    this->theSessionCallbackObject = session_object_val;
}

void GroupClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theGroupMgrObject->groupMgrLogit(s, str1_val);
}

void GroupClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theGroupMgrObject->groupMgrAbend(s, str1_val);
}
