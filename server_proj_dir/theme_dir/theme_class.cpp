/*
  Copyrights reserved
  Written by Paul Hwang
  File name: theme_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "theme_class.h"
#include "u_theme_dir/u_theme_class.h"
#include "d_theme_dir/d_theme_class.h"
#include "room_mgr_dir/room_mgr_class.h"
#include "room_mgr_dir/room_class.h"

ThemeClass::ThemeClass (void)
{
    memset(this, 0, sizeof(ThemeClass));
    this->theUThemeObject = new UThemeClass(this);
    this->theRoomMgrObject = new RoomMgrClass(this);
    this->theDThemeObject = new DThemeClass(this);
    this->theRoomListMgrObject = phwangMallocListMgr("ROOM", ROOM_MGR_PROTOCOL_ROOM_ID_SIZE, ROOM_MGR_PROTOCOL_ROOM_INDEX_SIZE, 700);

    this->debug(true, "ThemeClass", "init");
}

ThemeClass::~ThemeClass (void)
{
    this->theDThemeObject->~DThemeClass();
    this->theRoomMgrObject->~RoomMgrClass();
    this->theUThemeObject->~UThemeClass();
}

RoomClass *ThemeClass::mallocRoom (char *room_id_index_val)
{
    this->debug(true, "mallocGroup", "");

    int room_id = this->theRoomMgrObject->allocRoomId();
    int room_index = this->theRoomMgrObject->allocRoomIndex();
    if (room_index != -1) {
        RoomClass *room = new RoomClass(this->theRoomMgrObject, this, room_id, room_index, room_id_index_val);
        this->theRoomMgrObject->theRoomTableArray[room_index] = room;
        return room;
    }
    else {
        /* TBD */
    }
}

void ThemeClass::insertRoom (RoomClass *group_object_val)
{
    int i = 0;
    while (i < GAME_SERVER_ROOM_ARRAY_SIZE) {
        if (!this->theRoomTableArray[i]) {
            this->theRoomTableArray[i] = group_object_val;
            return;
        }
        i++;
    }
    this->abend("insertGroup", "table is full");
}

void ThemeClass::removeRoom (RoomClass *group_object_val)
{
    int i = 0;
    while (i < GAME_SERVER_ROOM_ARRAY_SIZE) {
        if (this->theRoomTableArray[i] == group_object_val) {
            this->theRoomTableArray[i] = 0;
            return;
        }
        i++;
    }
    this->abend("removeGroup", "not found");
}

RoomClass *ThemeClass::searchRoom (char *data_val)
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

    return this->theRoomMgrObject->getRoomByIdIndex(room_id, room_index);
}

void ThemeClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ThemeClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
