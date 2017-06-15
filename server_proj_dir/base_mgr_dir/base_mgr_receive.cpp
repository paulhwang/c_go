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
}






void baseMgrReceiveDataFromTransport (void *base_mgr_object_val, void *data_val);

void *baseMgrReceiveThreadFunction (void *this_val)
{
    ((BaseMgrClass *)this_val)->receiveThreadFunction();
}

void BaseMgrClass::receiveThreadFunction (void)
{
    if (1) {
        this->logit("receiveThreadFunction", "starts");
    }

    this->theTpTransferObject = phwangTpConnect(0, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, baseMgrReceiveDataFromTransport, this);

    this->receiveThreadLoop();
}

void BaseMgrClass::receiveThreadLoop (void)
{
    while (1) {
        char *data = (char *) phwangDequeue(this->theReceiveQueue);
        this->logit("receiveThreadLoop", data);
        if (data) {
            if (*data == BASE_MGR_PROTOCOL_COMMAND_IS_MALLOC_BASE) {
                data++;
                if (*data == BASE_MGR_PROTOCOL_GAME_NAME_IS_GO) {
                    this->mallocGoBase();
                }
            }
            else if (*data == BASE_MGR_PROTOCOL_COMMAND_IS_TRANSFER_DATA) {
                data++;
                this->receiveData(data);
            }
            else {
            }
        }
    }
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

void BaseMgrClass::exportAcceptConnection (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
    //phwangLogit("exportAcceptConnection", this->theTpTransferObject->objectName());
}

void BaseMgrClass::startThreads (void)
{
    this->startReceiveThread();
}
