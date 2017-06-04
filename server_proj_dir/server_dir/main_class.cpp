/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.cpp
*/

#include <stdio.h>
#include "../../utils_dir/logit_dir/logit.h"
#include "../../utils_dir/tp_dir/tp_class.h"
#include "../link_mgr_dir/link_mgr_class.h"
#include "../base_mgr_dir/base_mgr_class.h"
#include "main_class.h"

MainClass::MainClass(void)
{
    this->theTransportObject = new TpClass(this);
    this->theGoBaseMgrObject = new BaseMgrClass(this);
    this->theLinkMgrObject = new LinkMgrClass(this);
}

MainClass::~MainClass(void)
{
    this->theLinkMgrObject->~LinkMgrClass(); 
    this->theGoBaseMgrObject->~BaseMgrClass(); 
    this->theTransportObject->~TpClass(); 
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
    LOGIT(s, str1_val);
}

void MainClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    ABEND(s, str1_val);
}
