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

QueueClass::QueueClass(int do_suspend_val, int max_size_val)
{
    memset((char *) this, 0, sizeof (*this));
    this->theDoSuspend = do_suspend_val;
    this->theMaxQueueSize = max_size_val;

    if (!this->theMaxQueueSize) {
        this->theMaxQueueSize = QUEUE_CLASS_DEFAULT_MAX_QUEUE_SIZE;
    }

    if (this->theDoSuspend) {
        this->theSuspendObject = new SuspendClass();
    }
    else {
        this->theSuspendObject = 0;
    }

    this->theMutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(this->theMutex, NULL);
}

QueueClass::~QueueClass(void)
{
    if (this->theSuspendObject) {
        delete this->theSuspendObject;
    }
    free(this->theMutex);
}

void QueueClass::initQueue (void)
{
  //InitializeCriticalSectionAndSpinCount(&cs_queue, 0);
}

void QueueClass::enqueueData (void *data_val)
{
    this->debug(false, "enqueueData", (char *) data_val);

    /* queue is too big */
    if (this->theMaxQueueSize && (this->theQueueSize > this->theMaxQueueSize)) {
        delete data_val;
        this->abend("enqueueData", "queue full");
        return;
    }

    QueueEntryClass *entry = new QueueEntryClass();
    if (!entry) {
        this->abend("enqueueData", "fail to create new QueueEntryClass");
        return;
    }
    entry->data = data_val;

    this->abendQueue("enqueueData begin");
    pthread_mutex_lock(this->theMutex);
    this->enqueueEntry(entry);
    pthread_mutex_unlock(this->theMutex);
    this->abendQueue("enqueueData end");

    if (this->theSuspendObject) {
        this->theSuspendObject->signal();
    }
}

void *QueueClass::dequeueData (void)
{
    while (1) {
        QueueEntryClass *entry = this->dequeueEntry();
        if (entry) {
printf("***************QueueClass::dequeueData****** 2\n");
            void *data = entry->data;
printf("***************QueueClass::dequeueData****** 3\n");
            this->delete_entry(entry);
printf("***************QueueClass::dequeueData****** 4\n");

            this->debug(false, "dequeueData", (char *) data);
            return data;
        }
        else {
            if (this->theSuspendObject) {
                this->theSuspendObject->wait();
            }
            else {
                return 0;
            }
        }
    }
}

void QueueClass::enqueueEntry(QueueEntryClass *entry)
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

QueueEntryClass *QueueClass::dequeueEntry(void)
{
    QueueEntryClass *entry;

    if (!this->theQueueHead) {
        return 0;
    }

    this->abendQueue("dequeueEntry begin");

    pthread_mutex_lock(this->theMutex);

    if (this->theQueueSize == 1) {
        entry = this->theQueueHead;
        this->theQueueHead = this->theQueueTail = 0;
        this->theQueueSize = 0;
        pthread_mutex_unlock(this->theMutex);

        this->abendQueue("dequeueEntry end1");
        return entry;
    }

    entry = this->theQueueHead;
    this->theQueueHead = this->theQueueHead->next;
    this->theQueueHead->prev = 0;
    this->theQueueSize--;
    pthread_mutex_unlock(this->theMutex);

    this->abendQueue("dequeueEntry end2");
    return entry;
}

void QueueClass::abendQueue (char const *msg_val)
{
    QueueEntryClass *entry;
    int length;
 
    if (!this) {
        return;
    }
 
    pthread_mutex_lock(this->theMutex);
    length = 0;
    entry = this->theQueueHead;
    while (entry) {
        length++;
        entry = entry->next;
    }
 
    if (length != this->theQueueSize) {
        printf("%s length=%d %d\n", msg_val, length, this->theQueueSize);
        this->abend("abendQueue", "from head: bad length");
    }

    length = 0;
    entry = this->theQueueTail;
    while (entry) {
        length++;
        entry = entry->prev;
    }
 
    if (length != this->theQueueSize) {
        printf("%s length=%d %d\n", msg_val, length, this->theQueueSize);
        this->abend("abendQueue", "from tail: bad length");
    }

    pthread_mutex_unlock(this->theMutex);
}

void QueueClass::flush_queue(void)
{
    QueueEntryClass *entry, *entry_next; 
 
    pthread_mutex_lock(this->theMutex);
    entry = this->theQueueHead;
    while (entry) {
        entry_next = entry->next;
        delete_entry(entry);
        this->theQueueSize--;
        entry = entry_next;
    }
    this->theQueueHead = this->theQueueTail = 0;
 
    if (this->theQueueSize) {
        //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    }

    pthread_mutex_unlock(this->theMutex);
}

void QueueClass::delete_entry(QueueEntryClass *del_entry)
{
    delete del_entry;
}

void QueueClass::logit (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
}

void QueueClass::abend (char const* str0_val, char const* str1_val)
{
    phwangAbend(str0_val, str1_val);
}
