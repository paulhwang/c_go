/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/tp_dir/tp_server_class.h"
#include "../link_mgr_dir/link_mgr_class.h"
#include "../base_mgr_dir/base_mgr_class.h"
#include "main_class.h"

MainClass::MainClass(void)
{
    this->theTransportObject = new TpServerClass(this);
    this->theGoBaseMgrObject = new BaseMgrClass(this);
    this->theLinkMgrObject = new LinkMgrClass(this);
}

MainClass::~MainClass(void)
{
    this->theLinkMgrObject->~LinkMgrClass(); 
    this->theGoBaseMgrObject->~BaseMgrClass(); 
    this->theTransportObject->~TpServerClass(); 
}

void MainClass::startThreads (void)
{
    this->theGoBaseMgrObject->startThreads();
    this->theLinkMgrObject->startThreads();
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

