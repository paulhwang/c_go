/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_class_thread.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tp_class.h"

void *transportServerThreadFunction (void *data_val)
{
    unsigned short port = ((transport_thread_parameter *) data_val)->port;
    TpClass *transport_object = ((transport_thread_parameter *) data_val)->transport_object;
    free(data_val);

    transport_object->serverThreadFunction(port);
}

void TpClass::startServerThread (TpTransferClass *tp_transfer_val, unsigned short port_val)
{
    transport_thread_parameter *data = (transport_thread_parameter *) malloc(sizeof(transport_thread_parameter));
    data->port = port_val;
    data->transport_object = this;

    int r;
    if (0) {
        this->logit("startServerThread", "");
    }
    r = pthread_create(&this->theServerThread, 0, transportServerThreadFunction, data);
    if (r) {
        printf("Error - startServerThread() return code: %d\n", r);
        return;
    }
}

void mainReceiveDataFromTransport (void* engine_object_val, void *data_val);

void *transportClientThreadFunction (void *data_val)
{
    unsigned long ip_addr = ((transport_thread_parameter *) data_val)->ip_addr;
    unsigned short port = ((transport_thread_parameter *) data_val)->port;
    TpClass *transport_object = ((transport_thread_parameter *) data_val)->transport_object;
    free(data_val);

    printf("transportClientThreadFunction aaa %i\n", port);
    transport_object->clientThreadFunction(ip_addr, port, mainReceiveDataFromTransport);
    printf("transportClientThreadFunction bbb %i\n", port);
}

void TpClass::startClientThread (unsigned long ip_addr_val, ushort port_val)
{
    transport_thread_parameter *data = (transport_thread_parameter *) malloc(sizeof(transport_thread_parameter));
    data->ip_addr = ip_addr_val;
    data->port = port_val;
    data->transport_object = this;

    int r;
    if (1) {
        this->logit("startClientThread", "");
    }
    r = pthread_create(&this->theClientThread, 0, transportClientThreadFunction, data);
    if (r) {
        printf("Error - startClientThread() return code: %d\n", r);
        return;
    }
}
