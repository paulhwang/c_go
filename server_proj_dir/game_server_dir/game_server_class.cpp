/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_server_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "game_server_class.h"
#include "game_userver_dir/game_userver_class.h"
#include "game_dserver_dir/game_dserver_class.h"
#include "group_mgr_class.h"

GameServerClass::GameServerClass (void *main_object_val)
{
    memset(this, 0, sizeof(GameServerClass));
    this->theMainObject = main_object_val;
    this->theGameUServerObject = new GameUServerClass(this);
    this->theGameDServerObject = new GameDServerClass(this);

    this->theGroupMgrObject = new GroupMgrClass(this);

    if (1) {
        this->logit("GameServerClass", "init");
    }
}

GameServerClass::~GameServerClass (void)
{
}

void GameServerClass::startThreads (void)
{
    this->theGameUServerObject->startThreads();
    this->theGameDServerObject->startThreads();
}

void GameServerClass::insertGroup (GroupClass *group_object_val)
{
    int i = 0;
    while (i < GAME_SERVER_GROUP_ARRAY_SIZE) {
        if (!this->theGroupTableArray[i]) {
            this->theGroupTableArray[i] = group_object_val;
            return;
        }
        i++;
    }
    this->abend("insertGroup", "table is full");
}

void GameServerClass::removeGroup (GroupClass *group_object_val)
{
    int i = 0;
    while (i < GAME_SERVER_GROUP_ARRAY_SIZE) {
        if (this->theGroupTableArray[i] == group_object_val) {
            this->theGroupTableArray[i] = 0;
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
