/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_receive.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "base_mgr_class.h"

void BaseMgrClass::transmitFunction (char *data_val)
{
    this->logit("transmitFunction", data_val);
    phwangTpTransmit(this->theTpTransferObject, data_val);
}

void BaseMgrClass::receiveFunction (char *data_val)
{
    this->logit("receiveFunction", data_val);

    if (*data_val == BASE_MGR_PROTOCOL_COMMAND_IS_MALLOC_BASE) {
        data_val++;
        if (*data_val == BASE_MGR_PROTOCOL_GAME_NAME_IS_GO) {
            this->mallocGoBase();
        }
    }
    else if (*data_val == BASE_MGR_PROTOCOL_COMMAND_IS_TRANSFER_DATA) {
        data_val++;
        this->receiveData(data_val);
    }
    else {
    }
}

void BaseMgrClass::receiveThreadFunction (void)
{
    if (1) {
        this->logit("receiveThreadFunction", "starts");
    }

    this->startNetConnect();

    while (1) {
        void *data = phwangDequeue(this->theReceiveQueue);
        if (data) {
            this->receiveFunction((char *) data);
        }
    }
}

void *baseMgrReceiveThreadFunction (void *this_val)
{
    ((BaseMgrClass *)this_val)->receiveThreadFunction();
}

void BaseMgrClass::startReceiveThread (void)
{
    int r;

    if (0) {
        this->logit("startReceiveThread", "create receiveThread");
    }
    r = pthread_create(&this->theReceiveThread, NULL, baseMgrReceiveThreadFunction, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}
