/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_fabric_receive.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_fabric_class.h"

void UFabricClass::receiveFunction (char *data_val)
{
    this->logit("receiveFunction", data_val);
}

void UFabricClass::receiveThreadFunction (void)
{
    if (1) {
        this->logit("receiveThreadFunction", "starts");
    }

    while (1) {
        void *data = phwangDequeue(this->theReceiveQueue);
        if (data) {
            this->receiveFunction((char *) data);
        }
    }
}

void *uFabricReceiveThreadFunction (void *this_val)
{
    ((UFabricClass *)this_val)->receiveThreadFunction();
}

void UFabricClass::startReceiveThread (void)
{
    int r;

    if (0) {
        this->logit("startReceiveThread", "create receiveThread");
    }
    r = pthread_create(&this->theReceiveThread, NULL, uFabricReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}
