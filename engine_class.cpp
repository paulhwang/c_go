/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.cpp
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

    this->theGoReceiveQueue = new QueueMgrClass();
    this->goReceiveQueue()->initQueue(100);
}

EngineClass::~EngineClass(void)
{
    this->goReceiveQueue()->~QueueMgrClass();
    this->transportTransmitQueue()->~QueueMgrClass();
}

void EngineClass::goBaseMgrReceiveThreadLoop (void)
{
    if (1) {
        printf("BaseMgrThread starts\n");
    }
    this->goBaseMgrObject()->receiveThreadLoop();

}

void EngineClass::createTransportObject (void)
{
    if (1) {
        printf("TransportThread starts\n");
    }
    this->transportObject()->startServer(8001);
}

void* goBaseMgrReceiveThreadFunc (void* this_val)
{
    ((EngineClass *)this_val)->goBaseMgrReceiveThreadLoop();
}

void* createTransportFunction (void* this_val)
{
    ((EngineClass *)this_val)->createTransportObject();
}

void EngineClass::startEngine (void)
{
    if (0) {
        this->logit("startEngine", "create theGoThread");
    }
    int r = pthread_create(&this->theGoThread, NULL, goBaseMgrReceiveThreadFunc, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }

    if (0) {
        this->logit("startEngine", "create theTransportThread");
    }
    r = pthread_create(&this->theTransportThread, NULL, createTransportFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }

    this->goReceiveQueue()->enqueueData((void *) "Move   03031001");

    pthread_join(this->goThread(), NULL);
    pthread_join(this->transportThread(), NULL);
}
