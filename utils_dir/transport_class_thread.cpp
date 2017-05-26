/*
  Copyrights reserved
  Written by Paul Hwang
  File name: transport_class_thread.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "transport_class.h"

void *transportServerThreadFunction (void *data_val)
{
    unsigned short port = ((transport_thread_parameter *) data_val)->port;
    TransportClass *transport_object = ((transport_thread_parameter *) data_val)->transport_object;
    free(data_val);

    transport_object->serverThreadFunction(port);
}

void TransportClass::startServerThread (ushort port_val)
{
    transport_thread_parameter *data = (transport_thread_parameter *) malloc(sizeof(transport_thread_parameter));
    data->port = port_val;
    data->transport_object = this;

    int r;
    if (0) {
        this->logit("startServerThread", "");
    }
    r = pthread_create(&this->serverThread, 0, transportServerThreadFunction, data);
    if (r) {
        printf("Error - startServerThread() return code: %d\n", r);
        return;
    }
}

void *transportClientThreadFunction (void *data_val)
{
    unsigned short port = ((transport_thread_parameter *) data_val)->port;
    TransportClass *transport_object = ((transport_thread_parameter *) data_val)->transport_object;
    free(data_val);

    transport_object->serverThreadFunction(port);
}

void TransportClass::startClientThread (ushort port_val)
{
    transport_thread_parameter *data = (transport_thread_parameter *) malloc(sizeof(transport_thread_parameter));
    data->port = port_val;
    data->transport_object = this;

    int r;
    if (0) {
        this->logit("startClientThread", "");
    }
    r = pthread_create(&this->clientThread, 0, transportClientThreadFunction, data);
    if (r) {
        printf("Error - startClientThread() return code: %d\n", r);
        return;
    }
}
