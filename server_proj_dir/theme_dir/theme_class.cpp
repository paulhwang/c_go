/*
  Copyrights reserved
  Written by Paul Hwang
  File name: theme_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../protocol_dir/ft_command_class.h"
#include "theme_class.h"
#include "u_theme_dir/u_theme_class.h"
#include "d_theme_dir/d_theme_class.h"
#include "room_class.h"

ThemeClass::ThemeClass (int debug_code_val)
{
    memset(this, 0, sizeof(ThemeClass));
    this->theDebugCode = debug_code_val;
    
    this->theUThemeObject = new UThemeClass(this);
    this->theDThemeObject = new DThemeClass(this);
    this->theRoomListMgrObject = phwangListMgrMalloc("ROOM", FT_CommandClass::ROOM_ID_SIZE, FT_CommandClass::ROOM_INDEX_SIZE, 700);

    phwangDebugS(false, "ThemeClass::ThemeClass", "init");
}

ThemeClass::~ThemeClass (void)
{
    this->theDThemeObject->~DThemeClass();
    this->theUThemeObject->~UThemeClass();
    phwangDebugS(true, "ThemeClass::~ThemeClass", "exit");
}

RoomClass *ThemeClass::mallocRoom (char *room_id_index_val)
{
    RoomClass *room = new RoomClass(this->theRoomListMgrObject, this, room_id_index_val);
    if (!room) {
        phwangAbendS("ThemeClass::mallocRoom", "fail_to_malloc_room");
        return 0;
    }
    return room;
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
    phwangAbendS("ThemeClass::insertRoom", "table is full");
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
    phwangAbendS("ThemeClass::removeRoom", "not found");
}
