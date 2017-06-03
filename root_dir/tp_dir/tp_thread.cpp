/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_class_thread.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tp_class.h"
#include "tp_transfer_class.h"

void *transportServerThreadFunction (void *data_val)
{
    unsigned short port = ((transport_thread_parameter *) data_val)->port;
    TpClass *transport_object = ((transport_thread_parameter *) data_val)->transport_object;
    TpTransferClass *tp_transfer_object = ((transport_thread_parameter *) data_val)->tp_transfer_object;
    free(data_val);

    transport_object->serverThreadFunction(port, tp_transfer_object);
}

pthread_t TpClass::startServerThread (TpTransferClass *tp_transfer_object_val, unsigned short port_val)
{
    pthread_t thread;

    transport_thread_parameter *data = (transport_thread_parameter *) malloc(sizeof(transport_thread_parameter));
    data->port = port_val;
    data->transport_object = this;
    data->tp_transfer_object = tp_transfer_object_val;

    int r;
    if (0) {
        this->logit("startServerThread", "");
    }
    r = pthread_create(&thread, 0, transportServerThreadFunction, data);
    if (r) {
        printf("Error - startServerThread() return code: %d\n", r);
        return 0;
    }

    return thread;
}

TpTransferClass *TpClass::startServer (unsigned short port_val, void (*receive_callback_val)(void *, void *))
{
    TpTransferClass *tp_transfer_object = new TpTransferClass(this, receive_callback_val);
      if (tp_transfer_object) {
          this->startServerThread(tp_transfer_object, port_val);
          return tp_transfer_object;
    }
    else {
          return 0;
    }
}
