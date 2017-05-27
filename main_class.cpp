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
#include "engine_class.h"

EngineClass::EngineClass(void)
{
    this->theGoBaseMgrObject = new BaseMgrClass(this);
    this->theTransportObject = new TransportClass(this);

    this->theTransportTransmitQueue = new QueueMgrClass();
    this->transportTransmitQueue()->initQueue(100);
}

EngineClass::~EngineClass(void)
{
    this->transportTransmitQueue()->~QueueMgrClass();
}
