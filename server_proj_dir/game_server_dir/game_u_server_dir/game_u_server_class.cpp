/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_u_server_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "game_u_server_class.h"

GameUServerClass::GameUServerClass (GameServerClass *game_server_object_val)
{
    memset(this, 0, sizeof(GameUServerClass));
    this->theGameServerObject = game_server_object_val;
    this->theReceiveQueue = phwangMallocQueue(GAME_USERVER_RECEIVE_QUEUE_SIZE);
    this->startNetServer();

    if (1) {
        this->logit("GameUServerClass", "init");
    }
}

GameUServerClass::~GameUServerClass (void)
{
}

void GameUServerClass::startThreads (void)
{
    this->startReceiveThread();
}

void GameUServerClass::debug (int on_off_val, char const* str0_val, char const* str1_val)
{
    if (on_off_val) {
        this->logit(str0_val, str1_val);
    }
}

void GameUServerClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void GameUServerClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
