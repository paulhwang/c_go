/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_thread.cpp
*/

#include <stdio.h>
#include "../../utils_dir/phwang.h"
#include "../../utils_dir/tp_dir/tp_class.h"
#include "../server_dir/main_class.h"
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

void BaseMgrClass::receiveThreadLoop (void)
{
    while (1) {
        char *data = (char *) phwangDequeue(this->theReceiveQueue);
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

void baseMgrReceiveDataFromTransport (void *base_mgr_object_val, void *data_val) {
    LOGIT("Golbal::baseMgrReceiveDataFromTransport", (char *) data_val);
    ((BaseMgrClass *) base_mgr_object_val)->exportReceiveData(data_val);
}

void BaseMgrClass::startThreads (void)
{
    this->startReceiveThread();

    StartServerOutputStruct start_server_output;
    this->theMainObject->transportObject()->startServer(TRANSPORT_PORT_NUMBER_FOR_BASE_MGR, baseMgrReceiveDataFromTransport, this, &start_server_output);
    this->theTpTransferObject = start_server_output.tp_transfer_object;
    this->theTpServerThread = start_server_output.server_thread;
}