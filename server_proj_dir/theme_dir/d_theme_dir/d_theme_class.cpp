/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_theme_class.h"

GameDServerClass::GameDServerClass (ThemeClass *theme_object_val)
{
    memset(this, 0, sizeof(GameDServerClass));
    this->theThemeObject = theme_object_val;

    this->startNetConnect();

    if (1) {
        this->logit("GameDServerClass", "init");
    }
}

GameDServerClass::~GameDServerClass (void)
{
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
