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
