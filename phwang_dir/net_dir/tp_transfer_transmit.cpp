/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_transmit.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include "../../phwang_dir/phwang.h"
#include "tp_transfer_class.h"

void TpTransferClass::exportTransmitData (void *data_val)
{
    phwangEnqueue(this->theTransmitQueue, data_val);
}

void TpTransferClass::transmitThreadFunction(int socket_val)
{
    while (1) {
        char *data = (char *) phwangDequeue(this->theTransmitQueue, "TpTransferClass::transmitThreadFunction()");
        if (data) {
            int length = strlen(data);
            char *ptr;
            char *buf = ptr = (char *) malloc(length + (1 + 5 + 1 + 1) + 32);

            if (length < 1000) {
                *ptr++ = '{';
                phwangEncodeNumber(ptr, length, 3);
                ptr += 3;
                strcpy(ptr, data);
                ptr += length;
                *ptr++ = '}';
                *ptr = 0;
            }
            else {
                *ptr++ = '[';
                phwangEncodeNumber(ptr, length, 5);
                ptr += 5;
                strcpy(ptr, data);
                ptr += length;
                *ptr++ = ']';
                *ptr = 0;
            }
            this->debug(true, "transmitThreadFunction", (char *) data);
            this->debug(true, "transmitThreadFunction", (char *) buf);
            phwangFree(data, "TpTransferClass::transmitThreadFunction");
            send(socket_val, buf , strlen(buf) , 0);
        }
    }
}

void *tpTransferTransmitThreadFunction (void *data_val)
{
    int socket = ((tp_transfer_thread_parameter *) data_val)->socket;
    TpTransferClass *tp_transfer_object = ((tp_transfer_thread_parameter *) data_val)->tp_transfer_object;
    phwangFree(data_val, "tpTransferTransmitThreadFunction");

    tp_transfer_object->transmitThreadFunction(socket);
}

void TpTransferClass::startTransmitThread (int socket_val)
{
    tp_transfer_thread_parameter *data = (tp_transfer_thread_parameter *) phwangMalloc(sizeof(tp_transfer_thread_parameter));
    data->socket = socket_val;
    data->tp_transfer_object = this;

    this->debug(false, "startTransmitThread", "");

    int r = pthread_create(&this->theTransmitThread, 0, tpTransferTransmitThreadFunction, data);
    if (r) {
        printf("Error - startTransmitThread() return code: %d\n", r);
        return;
    }
}
