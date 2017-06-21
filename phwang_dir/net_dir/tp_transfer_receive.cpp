/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_receive.cpp
*/

#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <pwd.h>
#include "../../phwang_dir/phwang.h"
#include "tp_transfer_class.h"

void TpTransferClass::receiveThreadFunction(int socket_val)
{
    while (1) {
        char *data = (char *) malloc(TP_TRANSFER_CLASS_RECEIVE_BUFFER_SIZE);

        int length = read(socket_val, data, TP_TRANSFER_CLASS_RECEIVE_BUFFER_SIZE);
        if (length > 0) {
            this->debug(false, "receiveThreadFunction", data);
            phwangEnqueue(this->theReceiveQueue, data);
        }
        else {
            usleep(10);
        }
    }
}

void *tpTranferReceiveThreadFunction (void *data_val)
{
    int socket = ((tp_transfer_thread_parameter *) data_val)->socket;
    TpTransferClass *tp_transfer_object = ((tp_transfer_thread_parameter *) data_val)->tp_transfer_object;
    free(data_val);

    tp_transfer_object->receiveThreadFunction(socket);
}

void TpTransferClass::startReceiveThread (int socket_val)
{
    tp_transfer_thread_parameter *data = (tp_transfer_thread_parameter *) malloc(sizeof(tp_transfer_thread_parameter));
    data->socket = socket_val;
    data->tp_transfer_object = this;

    this->debug(false, "startReceiveThread", "");

    int r = pthread_create(&this->theReceiveThread, 0, tpTranferReceiveThreadFunction, data);
    if (r) {
        printf("Error - startReceiveThread() return code: %d\n", r);
        return;
    }
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/

void TpTransferClass::receiveThreadFunction2 (void)
{
    this->debug(false, "receiveThreadFunction2", "starts");

    while (1) {
        char *data = (char *) phwangDequeue(this->theReceiveQueue);
        if (data) {
            this->debug(false, "receiveThreadFunction2", data);

            this->receiveCallback()(this->theReceiveObject, data);
        }
    }
}

void *tpTranferReceiveThreadFunction2 (void *this_val)
{
    ((TpTransferClass *)this_val)->receiveThreadFunction2();
}

void TpTransferClass::startReceiveThread2 (void)
{
    this->debug(false, "startReceiveThread2", "create receiveThread");

    int r = pthread_create(&this->theReceiveThread2, NULL, tpTranferReceiveThreadFunction2, this);
    if (r) {
        printf("Error - pthread_create() return code: %d\n", r);
        return;
    }
}
