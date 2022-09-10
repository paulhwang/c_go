/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_entry_class.h
*/

#pragma once

#include <atomic>

class QueueEntryClass
{
    friend class QueueClass;
    static std::atomic<int> ObjectCount;

    char theObjectName[64];
    QueueEntryClass *next;
    QueueEntryClass *prev;
    void *data;

    void deleteQueueEntry(void);

public:
    QueueEntryClass(void);
    ~QueueEntryClass(void);
    char *objectName(void) {return this->theObjectName;}
};
