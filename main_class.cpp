/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.cpp
*/

#include <stdio.h>
#include "utils_dir/logit.h"
#include "utils_dir/transport_class.h"
#include "utils_dir/queue_mgr_class.h"
#include "root_dir/base_mgr_dir/base_mgr_class.h"
#include "main_class.h"

MainClass::MainClass(void)
{
    this->goBaseMgrObject = new BaseMgrClass(this);
    this->transportObject = new TransportClass(this);

    this->theTransportTransmitQueue = new QueueMgrClass();
    this->transportTransmitQueue()->initQueue(100);
}

MainClass::~MainClass(void)
{
    this->transportTransmitQueue()->~QueueMgrClass();
}

void MainClass::startThreads (void)
{
    this->transportObject->startServerThread(TRANSPORT_PORT_NUMBER_FOR_ME);
    this->goBaseMgrObject->startThreads();
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
