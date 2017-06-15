/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_receive.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_fabric_class.h"
#include "../fabric_class.h"
#include "../u_fabric_dir/u_fabric_class.h"

void DFabricClass::receiveFunction (char *data_val)
{
    this->logit("receiveFunction", data_val);
    this->theFabricObject->uFabricObject()->transmitFunction(data_val);
}

void DFabricClass::receiveThreadFunction (void)
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

void *dFabricReceiveThreadFunction (void *this_val)
{
    ((DFabricClass *)this_val)->receiveThreadFunction();
}

void DFabricClass::startReceiveThread (void)
{
    int r;

    if (0) {
        this->logit("startReceiveThread", "create receiveThread");
    }
    r = pthread_create(&this->theReceiveThread, NULL, dFabricReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}
