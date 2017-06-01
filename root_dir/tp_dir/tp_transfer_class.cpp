/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.cpp
*/

#include <stdio.h>
#include <malloc.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <pwd.h>
#include "../../includes/common.h"
#include "tp_transfer_class.h"
#include "tp_class.h"
#include "../../utils_dir/logit.h"
#include "../../utils_dir/queue_mgr_class.h"
#include "../../main_exports.h"

TpTransferClass::TpTransferClass (TpClass *tp_object_val)
{
    this->theTpObject = tp_object_val;

    this->theTransmitQueue = new QueueMgrClass();
    this->theTransmitQueue->initQueue(TP_TRANSFER_CLASS_TRANSMIT_QUEUE_SIZE);

    if (1) {
        this->logit("TpTransferClass", "init");
    }
}

TpTransferClass::~TpTransferClass (void)
{
}

void TpTransferClass::startThreads(int socket_val)
{
    this->theSocket = socket_val;
    this->startReceiveThread(this->theSocket);
    this->startTransmitThread(this->theSocket);
}

#define TRANSPORT_RECEIVE_BUFFER_SIZE 1024

void TpTransferClass::receiveThreadFunction(int socket_val)
{
    while (1) {
        char *buffer = (char *) malloc(TRANSPORT_RECEIVE_BUFFER_SIZE);

        int length = read(socket_val, buffer, TRANSPORT_RECEIVE_BUFFER_SIZE);
        this->logit("receiveThreadFunction", buffer);
        if (length > 0) {
            mainReceiveDataFromTransport(this->theTpObject->mainObject(), buffer);
        }
    }
}

void TpTransferClass::exportTransmitData (void *data_val)
{
    this->theTransmitQueue->enqueueData(data_val);
}

void TpTransferClass::transmitThreadFunction(int socket_val)
{
    while (1) {
        void *data = this->theTransmitQueue->dequeueData();
        if (data) {
            char *str_data = (char *) data;
            printf("transmitThreadFunction len=%d\n", strlen(str_data));
            this->logit("transmitThreadFunction", (char *) str_data);
            send(socket_val, str_data , strlen(str_data) , 0);
        }
    }
}

void TpTransferClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    LOGIT(s, str1_val);
}

void TpTransferClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    ABEND(s, str1_val);
}

