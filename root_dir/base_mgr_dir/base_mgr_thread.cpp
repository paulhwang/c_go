/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_thread.cpp
*/

#include <stdio.h>
#include "../../utils_dir/queue_mgr_class.h"
#include "base_mgr_class.h"
#include "base_mgr_protocol.h"

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

void BaseMgrClass::receiveThreadLoop (void)
{
    while (1) {
        char *data = (char *) this->theReceiveQueue->dequeueData();
        if (data) {
            if (*data == BASE_MGR_PROTOCOL_COMMAND_MALLOC_BASE) {
                data++;
                this->mallocGoBase();
            }
            else if (*data == 'd') {
                data++;
                this->receiveData(data);
            }
            else {
            }
        }
    }
}

void BaseMgrClass::startThreads (void)
{
    int r;

    if (0) {
        this->logit("startThreads", "create receiveThread");
    }
    r = pthread_create(&this->theReceiveThread, NULL, baseMgrReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
    pthread_join(this->theReceiveThread, NULL);
}
