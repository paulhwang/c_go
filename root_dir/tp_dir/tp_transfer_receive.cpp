/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_receive.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <malloc.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <pwd.h>
#include "tp_transfer_class.h"
#include "tp_class.h"

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

    int r;
    if (0) {
        this->logit("startReceiveThread", "");
    }
    r = pthread_create(&this->theReceiveThread, 0, tpTranferReceiveThreadFunction, data);
    if (r) {
        printf("Error - startReceiveThread() return code: %d\n", r);
        return;
    }
}

void TpTransferClass::receiveThreadFunction(int socket_val)
{
    while (1) {
        char *buffer = (char *) malloc(TP_TRANSFER_CLASS_RECEIVE_BUFFER_SIZE);

        int length = read(socket_val, buffer, TP_TRANSFER_CLASS_RECEIVE_BUFFER_SIZE);
        this->logit("receiveThreadFunction", buffer);
        if (length > 0) {
            this->receiveCallback(this->theTpObject->mainObject(), buffer);
        }
    }
}
