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

void EngineClass::goBaseMgrReceiveThreadLoop (void)
{
    if (1) {
        printf("goBaseMgrReceiveThreadLoop starts\n");
    }
    this->goBaseMgrObject()->receiveThreadLoop();

}

void EngineClass::startEngineThreads (void)
{
	int r;

    if (0) {
        this->logit("startEngine", "create theGoThread");
    }
    r = pthread_create(&this->theGoThread, NULL, goBaseMgrReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }

    this->transportObject()->startServerThread(8002);

    pthread_join(this->goThread(), NULL);
}
