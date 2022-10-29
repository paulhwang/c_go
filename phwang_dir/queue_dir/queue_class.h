/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_class.h
*/

#pragma once

#include <pthread.h>
class QueueEntryClass;
class SuspendClass;

class QueueClass
{
#define QUEUE_CLASS_DEFAULT_MAX_QUEUE_SIZE 256
public:
    static const int ENQUEUE_SUCCEED = 0;
    static const int ENQUEUE_NULL = 1;
    static const int ENQUEUE_INVALID_CLASS = 2;
    static const int ENQUEUE_FULL = 3;
    static const int ENQUEUE_NEW_ENTRY_FAIL = 4;

private:
    int debugOn_;
    char const *theWho;
    SuspendClass *theSuspendObject;
    int theQueueSize;
    QueueEntryClass *theQueueHead;
    QueueEntryClass *theQueueTail;
    int theMaxQueueSize;
    pthread_mutex_t theMutex;

    void enqueueEntry(QueueEntryClass *entry);
    QueueEntryClass *dequeueEntry(void);
    int queueSize(void) {return this->theQueueSize;}

    void abendQueue(char const *msg_val);
    void flushQueue(void);

public:
    QueueClass(
        int debug_on_val,
        int do_suspend_val,
        int max_size_val,
        char const *who_val);
    ~QueueClass(void);
    char const *objectName(void) {return "QueueClass";}
    
    char const *who(void) {return this->theWho;}
    int enqueueData(void *data_val);
    void *dequeueData(void);
};
