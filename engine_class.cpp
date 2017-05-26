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

    this->theGoReceiveQueue = new QueueMgrClass();
    this->goReceiveQueue()->initQueue(100);
}

EngineClass::~EngineClass(void)
{
    this->goReceiveQueue()->~QueueMgrClass();
    this->transportTransmitQueue()->~QueueMgrClass();
}

void EngineClass::receiveDataFromTransport (void *data_val) {
    this->goReceiveQueue()->enqueueData(data_val);
}

void EngineClass::transmitDataToTransport(void *data_val)
{
    this->logit("transmitDataToTransport", (char *) data_val);
}

void EngineClass::goBaseMgrReceiveThreadLoop (void)
{
    if (1) {
        printf("goBaseMgrReceiveThreadLoop starts\n");
    }
    this->goBaseMgrObject()->receiveThreadLoop();

}

void EngineClass::transportTransmitThreadLoop (void)
{
    if (1) {
        printf("transportTransmitThreadLoop starts\n");
    }
    this->transportObject()->startServerThread(8002);
}

void EngineClass::startEngineThreads (void)
{
    void *goBaseMgrReceiveThreadFunction (void *this_val);
    void *transportTransmitThreadFunction (void *this_val);

    if (0) {
        this->logit("startEngine", "create theGoThread");
    }
    int r = pthread_create(&this->theGoThread, NULL, goBaseMgrReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }

    if (0) {
        this->logit("startEngine", "create theTransportThread");
    }
    r = pthread_create(&this->theTransportThread, NULL, transportTransmitThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }

    //receiveDataFromTransportFunc(this, (void *) "Move   03031001");

    pthread_join(this->goThread(), NULL);
    pthread_join(this->transportThread(), NULL);
}
