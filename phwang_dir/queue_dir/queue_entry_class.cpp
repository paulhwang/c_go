/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_entry_class.cpp
*/

#include "../phwang.h"
#include "queue_entry_class.h"

std::atomic<int> QueueEntryClass::ObjectCount(0);

QueueEntryClass::QueueEntryClass (void)
{
    memset(this, 0, sizeof (*this));
    strcpy(this->theObjectName, "QueueEntryClass");
    phwangIncrementAtomicCount(&QueueEntryClass::ObjectCount, this->objectName(), 2000);
}

QueueEntryClass::~QueueEntryClass (void)
{
    phwangDecrementAtomicCount(&QueueEntryClass::ObjectCount, this->objectName());

    if (strcmp(this->objectName(), "QueueEntryClass")) {
        phwangAbendS("QueueEntryClass::~QueueEntryClass", this->objectName());
    }
    strcpy(this->theObjectName, "QueueEntryClassDummy");
}

void QueueEntryClass::deleteQueueEntry (void)
{
    delete this;
}
