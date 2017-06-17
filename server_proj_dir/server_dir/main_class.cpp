/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../fabric_dir/fabric_class.h"
#include "../base_mgr_dir/base_mgr_class.h"
#include "../game_server_dir/game_server_class.h"
#include "main_class.h"

MainClass::MainClass(void)
{
    this->theFabricObject = new FabricClass();
    this->theGoGameServerObject = new GameServerClass();
    this->theGoBaseMgrObject = new BaseMgrClass();
}

MainClass::~MainClass(void)
{
    this->theGoBaseMgrObject->~BaseMgrClass(); 
    this->theGoGameServerObject->~GameServerClass(); 
    this->theFabricObject->~FabricClass(); 
}

void MainClass::startThreads (void)
{
    this->theGoBaseMgrObject->startThreads();
}

void MainClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void MainClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}

