/*
  Copyrights reserved
  Written by Paul Hwang
  File name: port_class_transmit.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "port_class.h"

void PortClass::exportTransmitData (void *data_val)
{
    phwangEnqueue(this->theTransmitQueue, data_val);
}

void *PortClass::transmitThreadFunction (int socket_val)
{
    while (1) {
        char *data = (char *) phwangDequeue(this->theTransmitQueue, "PortClass::transmitThreadFunction()");
        if (data) {
            phwangDebugWSS(false, "PortClass::transmitThreadFunction", this->theWho, "data=", data);

            int length = strlen(data);
            char *ptr;
            char *buf = ptr = (char *) malloc(1 + TCP_IP_DEF::MAX_TCP_DATA_LEN_SIZE + length + 1 + 1);

            if (length <= TCP_IP_DEF::MAX_TCP_DATA_SIZE - (1 + TCP_IP_DEF::MAX_TCP_DATA_LEN_SIZE + 1)) {
                *ptr++ = '{';

                phwangEncodeNumber(ptr, length, TCP_IP_DEF::MAX_TCP_DATA_LEN_SIZE);
                ptr += TCP_IP_DEF::MAX_TCP_DATA_LEN_SIZE;

                strcpy(ptr, data);
                ptr += length;

                *ptr++ = '}';

                *ptr = 0;

                phwangDebugWS(false, "PortClass::transmitThreadFunction", this->theWho, buf);

                send(socket_val, buf , strlen(buf) , 0);
            }
            else {
                phwangDebugWSI(true, "PortClass::transmitThreadFunction", this->theWho, "length=", length);
                phwangAbendWS("PortClass::transmitThreadFunction", this->theWho, "*****LENGTH TOO BIG*****");
            }

            phwangFree(data);
        }
    }
    return 0;
}

void *tpTransferTransmitThreadFunction (void *data_val)
{
    int socket = ((tp_transfer_thread_parameter *) data_val)->socket;
    PortClass *tp_transfer_object = ((tp_transfer_thread_parameter *) data_val)->tp_transfer_object;
    phwangFree(data_val);

    return tp_transfer_object->transmitThreadFunction(socket);
}

void PortClass::startTransmitThread (int socket_val)
{
    tp_transfer_thread_parameter *data = (tp_transfer_thread_parameter *) phwangMalloc(sizeof(tp_transfer_thread_parameter), MallocClass::startTransmitThread);
    data->socket = socket_val;
    data->tp_transfer_object = this;

    phwangDebugWS(false, "PortClass::startTransmitThread", this->theWho, "");

    int r = phwangPthreadCreate(&this->theTransmitThread, 0, tpTransferTransmitThreadFunction, data);
    if (r) {
        printf("Error - startTransmitThread() return code: %d\n", r);
        return;
    }
}
