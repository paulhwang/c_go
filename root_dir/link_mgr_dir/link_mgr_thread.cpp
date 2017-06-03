/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_thread.cpp
*/

#include <stdio.h>
#include "../../utils_dir/queue_mgr_class.h"
#include "link_mgr_class.h"
#include "../tp_dir/tp_class.h"

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
        char *data = (char *) this->theReceiveQueue->dequeueData();
        if (data) {
            if (*data == LINK_MGR_PROTOCOL_COMMAND_IS_MALLOC_LINK) {
                data++;
                this->mallocLink(data);
            }
        }
    }
}

void LinkMgrClass::startReceiveThread (void)
{
    int r;

    if (0) {
        this->logit("startReceiveThread", "create receiveThread");
    }
    r = pthread_create(&this->theReceiveThread, NULL, linkMgrReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}

void LinkMgrClass::startThreads (void)
{
    this->startReceiveThread();

    StartServerOutputStruct start_server_output;
}
