/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_class_thread.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tp_server_class.h"
#include "tp_class.h"

void *transportServerThreadFunction (void *data_val)
{
    unsigned short port = ((transport_thread_parameter *) data_val)->port;
    TpClass *transport_object = ((transport_thread_parameter *) data_val)->transport_object;
    free(data_val);

    transport_object->serverThreadFunction(port);
}

void TpClass::startServerThread (TpServerClass *transport_server_val)
{
    transport_thread_parameter *data = (transport_thread_parameter *) malloc(sizeof(transport_thread_parameter));
    data->port = transport_server_val->port();
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

void *transportClientThreadFunction (void *data_val)
{
    unsigned long ip_addr = ((transport_thread_parameter *) data_val)->ip_addr;
    unsigned short port = ((transport_thread_parameter *) data_val)->port;
    TpClass *transport_object = ((transport_thread_parameter *) data_val)->transport_object;
    free(data_val);

    printf("transportClientThreadFunction aaa %i\n", port);
    transport_object->clientThreadFunction(ip_addr, port);
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

void *transportReceiveThreadFunction (void *data_val)
{
    int socket = ((transport_thread_parameter *) data_val)->socket;
    TpClass *transport_object = ((transport_thread_parameter *) data_val)->transport_object;
    free(data_val);

    transport_object->receiveThreadFunction(socket);
}

void TpClass::startReceiveThread (int socket_val)
{
    transport_thread_parameter *data = (transport_thread_parameter *) malloc(sizeof(transport_thread_parameter));
    data->socket = socket_val;
    data->transport_object = this;

    int r;
    if (0) {
        this->logit("startReceiveThread", "");
    }
    r = pthread_create(&this->receiveThread, 0, transportReceiveThreadFunction, data);
    if (r) {
        printf("Error - startReceiveThread() return code: %d\n", r);
        return;
    }
}

void *transportTransmitThreadFunction (void *data_val)
{
    int socket = ((transport_thread_parameter *) data_val)->socket;
    TpClass *transport_object = ((transport_thread_parameter *) data_val)->transport_object;
    free(data_val);

    transport_object->transmitThreadFunction(socket);
}

void TpClass::startTransmitThread (int socket_val)
{
    transport_thread_parameter *data = (transport_thread_parameter *) malloc(sizeof(transport_thread_parameter));
    data->socket = socket_val;
    data->transport_object = this;

    int r;
    if (0) {
        this->logit("startTransmitThread", "");
    }
    r = pthread_create(&this->transmitThread, 0, transportTransmitThreadFunction, data);
    if (r) {
        printf("Error - startTransmitThread() return code: %d\n", r);
        return;
    }
}
