/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_transmit.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "tp_transfer_class.h"

void TpTransferClass::exportTransmitData (void *data_val)
{
    phwangEnqueue(this->theTransmitQueue, data_val);
}

void *TpTransferClass::transmitThreadFunction(int socket_val)
{
    while (1) {
        char *data = (char *) phwangDequeue(this->theTransmitQueue, "TpTransferClass::transmitThreadFunction()");
        if (data) {
            if (0) { /* debug */
                char s[128];
                sprintf(s, "(%s) data=%s", this->theWho, data);
                this->debug(false, "transmitThreadFunction", s);
            }

            int length = strlen(data);
            char *ptr;
            char *buf = ptr = (char *) malloc(length + (1 + TpTransferClass::DATA_LENGTH_SIZE + 1 + 1) + 32);

            if (length < 1400) {
                *ptr++ = '{';
                phwangEncodeNumber(ptr, length, TpTransferClass::DATA_LENGTH_SIZE);
                ptr += TpTransferClass::DATA_LENGTH_SIZE;
                strcpy(ptr, data);
                ptr += length;
                *ptr++ = '}';
                *ptr = 0;

                this->debug(false, "transmitThreadFunction", buf);

                send(socket_val, buf , strlen(buf) , 0);
            }
            else {
                if (1) { /* debug */
                    char s[128];
                    sprintf(s, "(%s) length=%d", this->theWho, length);
                    this->debug(true, "transmitThreadFunction", s);
                }
                this->abend("transmitThreadFunction", "*****LENGTH TOO BIG*****");
            }

            phwangFree(data);
        }
    }
    return 0;
}

void *tpTransferTransmitThreadFunction (void *data_val)
{
    int socket = ((tp_transfer_thread_parameter *) data_val)->socket;
    TpTransferClass *tp_transfer_object = ((tp_transfer_thread_parameter *) data_val)->tp_transfer_object;
    phwangFree(data_val);

    return tp_transfer_object->transmitThreadFunction(socket);
}

void TpTransferClass::startTransmitThread (int socket_val)
{
    tp_transfer_thread_parameter *data = (tp_transfer_thread_parameter *) phwangMalloc(sizeof(tp_transfer_thread_parameter), MallocClass::startTransmitThread);
    data->socket = socket_val;
    data->tp_transfer_object = this;

    this->debug(false, "startTransmitThread", "");

    int r = phwangPthreadCreate(&this->theTransmitThread, 0, tpTransferTransmitThreadFunction, data);
    if (r) {
        printf("Error - startTransmitThread() return code: %d\n", r);
        return;
    }
}
