/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "room_class.h"
#include "room_mgr_class.h"

RoomClass::RoomClass (RoomMgrClass *group_mgr_object_val, int group_id_val, int group_index_val)
{
    memset(this, 0, sizeof(RoomClass));
    this->theGroupMgrObject = group_mgr_object_val;
    this->theRoomId = group_id_val;
    this->theRoomIndex = group_index_val;

    if (1) {
        this->logit("RoomClass", "init");
    }
}

RoomClass::~RoomClass (void)
{
}

void RoomClass::insertSession (SessionClass *session_object_val)
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

void RoomClass::removeSession (SessionClass *session_object_val)
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

void RoomClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theGroupMgrObject->groupMgrLogit(s, str1_val);
}

void RoomClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theGroupMgrObject->groupMgrAbend(s, str1_val);
}
