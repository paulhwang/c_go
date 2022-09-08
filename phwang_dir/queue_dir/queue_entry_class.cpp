/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_entry_class.cpp
*/

#include "../phwang.h"
#include "queue_entry_class.h"

int QueueEntryClass::ObjectCount = 0;
std::atomic<int> x(0);

QueueEntryClass::QueueEntryClass (void)
{
    memset(this, 0, sizeof (*this));
    strcpy(this->theObjectName, "QueueEntryClass");
    phwangIncrementObjectCount(&QueueEntryClass::ObjectCount, this->objectName(), 3);
}

QueueEntryClass::~QueueEntryClass (void)
{
    phwangDecrementObjectCount(&QueueEntryClass::ObjectCount);

    if (strcmp(this->objectName(), "QueueEntryClass")) {
        this->abend("~QueueEntryClass", this->objectName());
    }
    strcpy(this->theObjectName, "QueueEntryClassDummy");
}

void QueueEntryClass::deleteQueueEntry (void)
{
    delete this;
}

void QueueEntryClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void QueueEntryClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
