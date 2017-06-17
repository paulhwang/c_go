/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_server_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "game_server_class.h"
#include "game_u_server_dir/game_u_server_class.h"
#include "game_d_server_dir/game_d_server_class.h"
#include "room_mgr_dir/room_mgr_class.h"

GameServerClass::GameServerClass (void)
{
    memset(this, 0, sizeof(GameServerClass));
    this->theGameUServerObject = new GameUServerClass(this);
    this->theGameDServerObject = new GameDServerClass(this);
    this->theRoomMgrObject = new RoomMgrClass(this);

    if (1) {
        this->logit("GameServerClass", "init");
    }
}

GameServerClass::~GameServerClass (void)
{
    this->theRoomMgrObject->~RoomMgrClass();
}

void GameServerClass::startThreads (void)
{
    this->theGameDServerObject->startThreads();
}

void GameServerClass::insertRoom (RoomClass *group_object_val)
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

void GameServerClass::removeRoom (RoomClass *group_object_val)
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

void GameServerClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void GameServerClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
