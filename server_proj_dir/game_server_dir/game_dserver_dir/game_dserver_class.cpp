/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_dserver_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "game_dserver_class.h"

GameDServerClass::GameDServerClass (GameServerClass *game_server_object_val)
{
    memset(this, 0, sizeof(GameDServerClass));
    this->theGameServerObject = game_server_object_val;
    this->theReceiveQueue = phwangMallocQueue(GAME_DSERVER_RECEIVE_QUEUE_SIZE);

    if (1) {
        this->logit("GameDServerClass", "init");
    }
}

GameDServerClass::~GameDServerClass (void)
{
}

void GameDServerClass::startThreads (void)
{
    this->startReceiveThread();
}

void GameDServerClass::debug (int on_off_val, char const* str0_val, char const* str1_val)
{
    if (on_off_val) {
        this->logit(str0_val, str1_val);
    }
}

void GameDServerClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void GameDServerClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
