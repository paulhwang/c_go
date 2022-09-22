/*
  Copyrights reserved
  Written by Paul Hwang
  File name: port_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "port_class.h"

std::atomic<int> PortClass::ObjectCount(0);

int PortClass::objectCount(void) {return PortClass::ObjectCount;}

PortClass::PortClass (int socket_val,
                                  void (*receive_callback_val)(void *, void *, void *),
                                  void *receive_object_val,
                                  char const *who_val)
{
    memset(this, 0, sizeof(*this));
    phwangIncrementAtomicCount(&PortClass::ObjectCount, this->objectName(), 6);
    this->theSocket = socket_val;
    this->theReceiveCallback = receive_callback_val;
    this->theReceiveObject = receive_object_val;
    this->theWho = who_val;
    this->setMaxDataSize();

    strcpy(this->theWhoForReceiveQueue, this->objectName());
    strcat(this->theWhoForReceiveQueue, ":");
    strcat(this->theWhoForReceiveQueue, this->theWho);
    strcat(this->theWhoForReceiveQueue, ":Transmit");
    this->theReceiveQueue = phwangMallocSuspendedQueue(PortClass::RECEIVE_QUEUE_SIZE, this->theWhoForReceiveQueue);

    strcpy(this->theWhoForTransmitQueue, this->objectName());
    strcat(this->theWhoForTransmitQueue, ":");
    strcat(this->theWhoForTransmitQueue, this->theWho);
    strcat(this->theWhoForTransmitQueue, ":Receive");
    this->theTransmitQueue = phwangMallocSuspendedQueue(PortClass::TRANSMIT_QUEUE_SIZE, this->theWhoForTransmitQueue);

    phwangDebugWS(false, "PortClass::PortClass", this->theWho, "init");
}

PortClass::~PortClass (void)
{
    phwangDecrementAtomicCount(&PortClass::ObjectCount, this->theWhoForReceiveQueue);
}

void PortClass::startThreads (int index_val)
{
    phwangDebugWSI(true, "PortClass::startThreads", this->theWho, "index", index_val);

    this->theIndex = index_val;
    this->startReceiveThread2();
    this->startReceiveThread(this->theSocket);
    this->startTransmitThread(this->theSocket);
}
