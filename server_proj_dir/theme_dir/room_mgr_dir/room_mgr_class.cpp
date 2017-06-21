/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_mgr_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "room_mgr_class.h"
#include "room_class.h"

RoomMgrClass::RoomMgrClass (ThemeClass *theme_object_val)
{
    memset(this, 0, sizeof(RoomMgrClass));
    this->theThemeObject = theme_object_val;
    this->theGlobalGroupId = 700;

    this->debug(true, "RoomMgrClass", "init");
}

RoomMgrClass::~RoomMgrClass (void)
{
}

int RoomMgrClass::allocRoomId (void)
{
    if (this->theGlobalGroupId >= GROUP_MGR_MAX_GLOBAL_GROUP_ID) {
        this->theGlobalGroupId = 0;
    }
    this->theGlobalGroupId++;
    return this->theGlobalGroupId;
}

int RoomMgrClass::allocRoomIndex (void)
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

RoomClass *RoomMgrClass::mallocRoom (char *group_id_index_val)
{
    if (1) {
        this->logit("mallocGroup", "");
    }
    int room_id = this->allocRoomId();
    int room_index = this->allocRoomIndex();
    if (room_index != -1) {
        RoomClass *room = new RoomClass(this, room_id, room_index, group_id_index_val);
        this->theGroupTableArray[room_index] = room;
        return room;
    }
    else {
        /* TBD */
    }
}

void RoomMgrClass::groupMgrLogit (char const* str0_val, char const* str1_val) {
    phwangLogit(str0_val, str1_val);
}

void RoomMgrClass::groupMgrAbend (char const* str0_val, char const* str1_val) {
    phwangAbend(str0_val, str1_val);
}

void RoomMgrClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->groupMgrLogit(s, str1_val);
}

void RoomMgrClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->groupMgrAbend(s, str1_val);
}

