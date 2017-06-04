/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.cpp
*/

#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <pwd.h>
#include "../../phwang_dir/phwang.h"
#include "tp_transfer_class.h"
#include "tp_class.h"

TpTransferClass::TpTransferClass (TpClass *tp_object_val, void (*receive_callback_val)(void *, void *), void *receive_object_val)
{
    this->theTpObject = tp_object_val;
    this->theReceiveCallback = receive_callback_val;
    this->theReceiveObject = receive_object_val;

    this->theTransmitQueue = phwangMallocQueue(TP_TRANSFER_CLASS_TRANSMIT_QUEUE_SIZE);

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

void TpTransferClass::exportTransmitData (void *data_val)
{
    phwangEnqueue(this->theTransmitQueue, data_val);
}

void TpTransferClass::transmitThreadFunction(int socket_val)
{
    while (1) {
        void *data = phwangDequeue(this->theTransmitQueue);
        if (data) {
            char *str_data = (char *) data;
            //printf("transmitThreadFunction len=%d\n", strlen(str_data));
            this->logit("transmitThreadFunction", (char *) str_data);
            send(socket_val, str_data , strlen(str_data) , 0);
        }
    }
}

void TpTransferClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void TpTransferClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
