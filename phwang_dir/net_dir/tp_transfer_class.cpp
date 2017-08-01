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

TpTransferClass::TpTransferClass (int socket_val,
                                  void (*receive_callback_val)(void *, void *, void *),
                                  void *receive_object_val)
{
    this->theSocket = socket_val;
    this->theReceiveCallback = receive_callback_val;
    this->theReceiveObject = receive_object_val;

    this->theReceiveQueue = phwangMallocSuspendedQueue(TP_TRANSFER_CLASS_RECEIVE_QUEUE_SIZE);
    this->theTransmitQueue = phwangMallocSuspendedQueue(TP_TRANSFER_CLASS_TRANSMIT_QUEUE_SIZE);

    this->debug(true, "TpTransferClass", "init");
}

TpTransferClass::~TpTransferClass (void)
{
}

void TpTransferClass::startThreads (int index_val)
{
    printf("index_val=%d(((((((((((((((((((((((((((((((((((((((\n", index_val);
    phwangLogit("TpTransferClass::startThreads", "((((((((((((((((((((((((((((((((((((((");
    this->theIndex = index_val;
    this->startReceiveThread2();
    this->startReceiveThread(this->theSocket);
    this->startTransmitThread(this->theSocket);
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

