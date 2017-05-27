/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_thread.cpp
*/

#include <stdio.h>
#include "base_mgr_class.h"

void *baseMgrReceiveThreadFunction (void *this_val)
{
    ((BaseMgrClass *)this_val)->receiveThreadFunction();
}

void BaseMgrClass::receiveThreadFunction (void)
{
    if (1) {
        this->logit("receiveThreadFunction", "starts");
    }
    this->receiveThreadLoop();

}

void BaseMgrClass::startThreads (void)
{
	int r;

    if (0) {
        this->logit("startThreads", "create receiveThread");
    }
    r = pthread_create(&this->receiveThread, NULL, baseMgrReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}
