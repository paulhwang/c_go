/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_class.cpp
*/

#include <string.h>
#include <stdlib.h>
#include "../phwang.h"
#include "queue_class.h"
#include "queue_entry_class.h"
#include "../suspend_dir/suspend_class.h"

QueueClass::QueueClass (
    int debug_on_val,
    int do_suspend_val,
    int max_size_val,
    char const *who_val)
{
    memset(this, 0, sizeof (*this));
    this->debugOn_ = true && debug_on_val;
    this->theWho = who_val;
    this->theMaxQueueSize = max_size_val;

    if (do_suspend_val) {
        this->theSuspendObject = new SuspendClass();
    }
    else {
        this->theSuspendObject = 0;
    }

    if (!this->theMaxQueueSize) {
        this->theMaxQueueSize = QUEUE_CLASS_DEFAULT_MAX_QUEUE_SIZE;
    }

    if (pthread_mutex_init(&this->theMutex, NULL) != 0) {
        phwangAbendWS("QueueClass::QueueClass", this->theWho, "pthread_mutex_init fail");
    }

    if (true && this->debugOn_) {
        printf("QueueClass::QueueClass(%s) init\n", this->theWho);
    }
}

QueueClass::~QueueClass (void)
{
    delete this->theSuspendObject;
}

int QueueClass::enqueueData (void *data_val)
{
    if (false && this->debugOn_) {
        printf("QueueClass::enqueueData(%s) %s\n", this->theWho, (char *) data_val);
    }

    /* queue is too big */
    if (this->theMaxQueueSize && (this->theQueueSize > this->theMaxQueueSize)) {
        phwangAbendWS("QueueClass::enqueueData", this->theWho, "queue full");
        return QueueClass::ENQUEUE_FULL;
    }

    QueueEntryClass *entry = new QueueEntryClass();
    if (!entry) {
        phwangAbendWS("QueueClass::enqueueData", this->theWho, "fail to create new QueueEntryClass");
        return QueueClass::ENQUEUE_NEW_ENTRY_FAIL;
    }
    entry->data = data_val;

    this->abendQueue("enqueueData begin");
    pthread_mutex_lock(&this->theMutex);
    this->enqueueEntry(entry);
    pthread_mutex_unlock(&this->theMutex);
    this->abendQueue("enqueueData end");

    if (this->theSuspendObject) {
        this->theSuspendObject->signal();
    }

    return QueueClass::ENQUEUE_SUCCEED;
}

void *QueueClass::dequeueData (void)
{
    while (1) {
        if (!this->theQueueHead) {
            if (!this->theSuspendObject) {
                return 0;
            }
            this->theSuspendObject->wait();
        }
        else {
            this->abendQueue("dequeueData begin");
            pthread_mutex_lock(&this->theMutex);
            QueueEntryClass *entry = this->dequeueEntry();
            pthread_mutex_unlock(&this->theMutex);
            this->abendQueue("dequeueData end");

            if (entry) {
                if (strcmp(entry->objectName(), "QueueEntryClass")) {
                    phwangAbendWS("QueueClass::dequeueData", this->theWho, "bad objectName");
                }
                void *data = entry->data;
                delete entry;

                if (false && this->debugOn_) {
                    printf("QueueClass::dequeueData(%s) %s\n", this->theWho, (char *) data);
                }
                return data;
            }
        }
    }
}

void QueueClass::enqueueEntry (QueueEntryClass *entry)
{
    if (!this->theQueueHead) {
        entry->next = 0;  
        entry->prev = 0;
        this->theQueueHead = entry;
        this->theQueueTail = entry;
        this->theQueueSize = 1; 
    }
    else {        
        entry->next = 0;  
        entry->prev = this->theQueueTail;
        this->theQueueTail->next = entry;
        this->theQueueTail = entry;
        this->theQueueSize++;
    }
}

QueueEntryClass *QueueClass::dequeueEntry (void)
{
    QueueEntryClass *entry;

    if (this->theQueueSize == 0) {
        phwangAbendWS("QueueClass::dequeueEntry", this->theWho, "theQueueSize == 0");
        return 0;
    }

    if (this->theQueueSize == 1) {
        entry = this->theQueueHead;
        this->theQueueHead = this->theQueueTail = 0;
        this->theQueueSize = 0;
        return entry;
    }

    entry = this->theQueueHead;
    this->theQueueHead = this->theQueueHead->next;
    this->theQueueHead->prev = 0;
    this->theQueueSize--;

    return entry;
}

void QueueClass::abendQueue (char const *msg_val)
{
    QueueEntryClass *entry;
    int length;
 
    if (!this) {
        phwangAbendWS("QueueClass::abendQueue", this->theWho, "null this");
        return;
    }
 
    if (this->theQueueSize == 0) {
        if (this->theQueueHead || this->theQueueTail) {
            phwangAbendWS("QueueClass::abendQueue", this->theWho, "theQueueSize == 0");
            return;
        }
    }
    else {
        if (!this->theQueueHead) {
            phwangAbendWS("QueueClass::abendQueue", this->theWho, "null theQueueHead");
            return;
        }
    }

    pthread_mutex_lock(&this->theMutex);
    length = 0;
    entry = this->theQueueHead;
    while (entry) {
        length++;
        entry = entry->next;
    }
 
    if (length != this->theQueueSize) {
        printf("%s length=%d %d\n", msg_val, length, this->theQueueSize);
        phwangAbendWS("QueueClass::abendQueue", this->theWho, "from head: bad length");
    }

    length = 0;
    entry = this->theQueueTail;
    while (entry) {
        length++;
        entry = entry->prev;
    }
 
    if (length != this->theQueueSize) {
        printf("%s length=%d %d\n", msg_val, length, this->theQueueSize);
        phwangAbendWS("QueueClass::abendQueue", this->theWho, "from tail: bad length");
    }

    pthread_mutex_unlock(&this->theMutex);
}

void QueueClass::flushQueue (void)
{
    QueueEntryClass *entry, *entry_next; 
 
    pthread_mutex_lock(&this->theMutex);
    entry = this->theQueueHead;
    while (entry) {
        entry_next = entry->next;
        phwangFree(entry->data);
        delete entry;
        this->theQueueSize--;
        entry = entry_next;
    }
    this->theQueueHead = this->theQueueTail = 0;
 
    if (this->theQueueSize) {
        phwangAbendWS("QueueClass::flushQueue", this->theWho, "theQueueSize");
    }

    pthread_mutex_unlock(&this->theMutex);
}
