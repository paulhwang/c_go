/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_transmit.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tp_transfer_class.h"

void *tpTransferTransmitThreadFunction (void *data_val)
{
    int socket = ((tp_transfer_thread_parameter *) data_val)->socket;
    TpTransferClass *tp_transfer_object = ((tp_transfer_thread_parameter *) data_val)->tp_transfer_object;
    free(data_val);

    tp_transfer_object->transmitThreadFunction(socket);
}

void TpTransferClass::startTransmitThread (int socket_val)
{
    tp_transfer_thread_parameter *data = (tp_transfer_thread_parameter *) malloc(sizeof(tp_transfer_thread_parameter));
    data->socket = socket_val;
    data->tp_transfer_object = this;

    this->debug(false, "startTransmitThread", "");

    int r = pthread_create(&this->theTransmitThread, 0, tpTransferTransmitThreadFunction, data);
    if (r) {
        printf("Error - startTransmitThread() return code: %d\n", r);
        return;
    }
}
