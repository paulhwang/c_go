/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_u_server_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_theme_class.h"

GameUServerClass::GameUServerClass (GameServerClass *game_server_object_val)
{
    memset(this, 0, sizeof(GameUServerClass));
    this->theGameServerObject = game_server_object_val;
    this->startNetServer();

    if (1) {
        this->logit("GameUServerClass", "init");
    }
}

GameUServerClass::~GameUServerClass (void)
{
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
