/*
  Copyrights reserved
  Written by Paul Hwang
  File name: theme_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../define_dir/ft_def.h"
#include "theme_class.h"
#include "u_theme_dir/u_theme_class.h"
#include "d_theme_dir/d_theme_class.h"
#include "room_class.h"

ThemeClass::ThemeClass (int debug_on_val)
{
    memset(this, 0, sizeof(ThemeClass));
    this->debugOn_ = true && debug_on_val;
    this->theDebugCode = debug_on_val;
    
    this->theUThemeObject = new UThemeClass(this->debugOn_, this);
    this->theDThemeObject = new DThemeClass(this->debugOn_, this);
    this->theRoomListMgrObject = phwangListMgrMalloc(this->debugOn_, "ROOM", SIZE_DEF::ROOM_ID_SIZE, SIZE_DEF::ROOM_INDEX_SIZE, SIZE_DEF::ROOM_ID_INITIAL_VALUE);

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
    RoomClass *room = new RoomClass(this->debugOn_, this->theRoomListMgrObject, this, room_id_index_val);
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
