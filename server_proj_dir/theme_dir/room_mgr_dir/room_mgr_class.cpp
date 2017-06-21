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
    this->theGlobalRoomId = 700;

    this->debug(true, "RoomMgrClass", "init");
}

RoomMgrClass::~RoomMgrClass (void)
{
}

int RoomMgrClass::allocRoomId (void)
{
    if (this->theGlobalRoomId >= ROOM_MGR_MAX_GLOBAL_ROOM_ID) {
        this->theGlobalRoomId = 0;
    }
    this->theGlobalRoomId++;
    return this->theGlobalRoomId;
}

int RoomMgrClass::allocRoomIndex (void)
{
    int index = 0;
    while (index < ROOM_MGR_ROOM_ARRAY_SIZE) {
        if (!this->theRoomTableArray[index]) {
            return index;
        }
        index++;
    }
    return -1;
}

RoomClass *RoomMgrClass::mallocRoom (char *room_id_index_val)
{
    if (1) {
        this->logit("mallocGroup", "");
    }
    int room_id = this->allocRoomId();
    int room_index = this->allocRoomIndex();
    if (room_index != -1) {
        RoomClass *room = new RoomClass(this, room_id, room_index, room_id_index_val);
        this->theRoomTableArray[room_index] = room;
        return room;
    }
    else {
        /* TBD */
    }
}

RoomClass *RoomMgrClass::searchRoom (char *data_val)
{
    int room_id;
    int room_index;

    this->debug(true, "searchRoom", data_val);

    phwangDecodeIdIndex(data_val,
                &room_id,
                ROOM_MGR_PROTOCOL_ROOM_ID_SIZE,
                &room_index,
                ROOM_MGR_PROTOCOL_ROOM_INDEX_SIZE);

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "room_id=%d room_index=%d", room_id, room_index);
        this->logit("searchRoom", s);
    }

    return this->getRoomByIdIndex(room_id, room_index);
}

RoomClass *RoomMgrClass::getRoomByIdIndex (int room_id_val, int room_index_val)
{
    if (room_id_val > ROOM_MGR_MAX_GLOBAL_ROOM_ID) {
        this->abend("getRoomByIdIndex", "room_id_val too big");
        return 0;
    }

    if (room_index_val >= ROOM_MGR_ROOM_ARRAY_SIZE) {
        this->abend("getRoomByIdIndex", "room_index_val too big");
        return 0;
    }

    RoomClass *room = this->theRoomTableArray[room_index_val];
    if (!room) {
        this->abend("getRoomByIdIndex", "null room");
        return 0;
    }

    if (room->roomId() != room_id_val){
        this->abend("getRoomByIdIndex", "room id does not match");
        return 0;
    }

    return room;
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

