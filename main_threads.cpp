/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_threads.cpp
*/

#include <stdio.h>
#include "utils_dir/transport_class.h"
#include "root_dir/base_mgr_dir/base_mgr_class.h"
#include "engine_class.h"

void *goBaseMgrReceiveThreadFunction (void *this_val)
{
    ((EngineClass *)this_val)->goBaseMgrReceiveThreadLoop();
}

void *transportTransmitThreadFunction1 (void *this_val)
{
    ((EngineClass *)this_val)->transportTransmitThreadLoop();
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
}

void EngineClass::startEngineThreads (void)
{
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
    r = pthread_create(&this->theTransportThread, NULL, transportTransmitThreadFunction1, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }

    this->transportObject()->startServerThread(8002);

    pthread_join(this->goThread(), NULL);
    pthread_join(this->transportThread(), NULL);
}
