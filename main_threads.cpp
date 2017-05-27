/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_threads.cpp
*/

#include <stdio.h>
#include "utils_dir/transport_class.h"
#include "root_dir/base_mgr_dir/base_mgr_class.h"
#include "main_class.h"

void *goBaseMgrReceiveThreadFunction (void *this_val)
{
    ((MainClass *)this_val)->goBaseMgrReceiveThreadLoop();
}

void MainClass::goBaseMgrReceiveThreadLoop (void)
{
    if (1) {
        printf("goBaseMgrReceiveThreadLoop starts\n");
    }
    this->goBaseMgrObject->receiveThreadLoop();

}

void MainClass::startEngineThreads (void)
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

    //this->transportObject->startServerThread(TRANSPORT_PORT_NUMBER_FOR_ME);

    pthread_join(this->goThread(), NULL);
}
