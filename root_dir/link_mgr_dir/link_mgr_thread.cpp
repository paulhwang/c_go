/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_thread.cpp
*/

#include <stdio.h>
#include "../../utils_dir/queue_mgr_class.h"
#include "link_mgr_class.h"

void *linkMgrReceiveThreadFunction (void *this_val)
{
    ((LinkMgrClass *)this_val)->receiveThreadFunction();
}

void LinkMgrClass::receiveThreadFunction (void)
{
    if (1) {
        this->logit("receiveThreadFunction", "starts");
    }
    this->receiveThreadLoop();

}

void LinkMgrClass::receiveThreadLoop (void)
{
    while (1) {
        char *data = (char *) this->receiveQueue->dequeueData();
        if (data) {
        }
    }
}

void LinkMgrClass::startThreads (void)
{
    int r;

    if (0) {
        this->logit("startThreads", "create receiveThread");
    }
    r = pthread_create(&this->receiveThread, NULL, linkMgrReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
    pthread_join(this->receiveThread, NULL);
}
