/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_entry_class.cpp
*/

#include "../phwang.h"
#include "queue_entry_class.h"

QueueEntryClass::QueueEntryClass(void)
{
    memset((char *) this, 0, sizeof (*this));
}

QueueEntryClass::~QueueEntryClass(void)
{
}

void QueueEntryClass::deleteQueueEntry(void)
{
    delete this;
}
