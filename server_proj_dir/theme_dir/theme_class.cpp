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

ThemeClass::ThemeClass (void)
{
    memset(this, 0, sizeof(ThemeClass));
    this->theGameUServerObject = new GameUServerClass(this);
    this->theRoomMgrObject = new RoomMgrClass(this);
    this->theGameDServerObject = new GameDServerClass(this);

    if (1) {
        this->logit("ThemeClass", "init");
    }
}

ThemeClass::~ThemeClass (void)
{
    this->theGameDServerObject->~GameDServerClass();
    this->theRoomMgrObject->~RoomMgrClass();
    this->theGameUServerObject->~GameUServerClass();
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
