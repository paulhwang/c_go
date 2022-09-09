/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/abend_dir/abend_class.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "tp_transfer_class.h"

std::atomic<int> TpTransferClass::ObjectCount(0);

int TpTransferClass::objectCount(void) {return TpTransferClass::ObjectCount;}

TpTransferClass::TpTransferClass (int socket_val,
                                  void (*receive_callback_val)(void *, void *, void *),
                                  void *receive_object_val,
                                  char const *who_val)
{
    memset(this, 0, sizeof(*this));
    phwangIncrementAtomicCount(&TpTransferClass::ObjectCount, this->objectName(), 5);
    this->theSocket = socket_val;
    this->theReceiveCallback = receive_callback_val;
    this->theReceiveObject = receive_object_val;
    this->theWho = who_val;
    this->setMaxDataSize();

    strcpy(this->theWhoForReceiveQueue, this->objectName());
    strcat(this->theWhoForReceiveQueue, ":");
    strcat(this->theWhoForReceiveQueue, this->theWho);
    strcat(this->theWhoForReceiveQueue, ":Transmit");
    this->theReceiveQueue = phwangMallocSuspendedQueue(TpTransferClass::RECEIVE_QUEUE_SIZE, this->theWhoForReceiveQueue);

    strcpy(this->theWhoForTransmitQueue, this->objectName());
    strcat(this->theWhoForTransmitQueue, ":");
    strcat(this->theWhoForTransmitQueue, this->theWho);
    strcat(this->theWhoForTransmitQueue, ":Receive");
    this->theTransmitQueue = phwangMallocSuspendedQueue(TpTransferClass::TRANSMIT_QUEUE_SIZE, this->theWhoForTransmitQueue);

    phwangDebugWS(false, "TpTransferClass::TpTransferClass", this->theWho, "init");
}

TpTransferClass::~TpTransferClass (void)
{
    phwangDecrementAtomicCount(&TpTransferClass::ObjectCount, this->theWhoForReceiveQueue);
}

void TpTransferClass::startThreads (int index_val)
{
    phwangDebugWSI(true, "TpTransferClass::startThreads", this->theWho, "index", index_val);

    this->theIndex = index_val;
    this->startReceiveThread2();
    this->startReceiveThread(this->theSocket);
    this->startTransmitThread(this->theSocket);
}
