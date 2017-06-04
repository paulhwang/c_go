/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue.cpp
*/

#include "../phwang.h"
#include "queue_class.h"

void *phwangMallocQueue (int size_val)
{
    QueueMgrClass *queue = new QueueMgrClass();
    return queue;
}

void phwangFreeQueue (void *queue_val)
{
    if (!queue_val) {
        phwangLogit("phwangFreeQueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueMgrClass *) queue_val)->objectName(), "QueueMgrClass")) {
        phwangLogit("phwangFreeQueue", "wrong object");
        return;
    }

    ((QueueMgrClass *) queue_val)->~QueueMgrClass();
}

void phwangEnqueue (void *queue_val, void *data_val)
{
    if (!queue_val) {
        phwangLogit("phwangEnqueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueMgrClass *) queue_val)->objectName(), "QueueMgrClass")) {
        phwangLogit("phwangEnqueue", "wrong object");
        return;
    }

    ((QueueMgrClass *) queue_val)->enqueueData(data_val);
}

void *phwangDequeue (void *queue_val)
{
    if (!queue_val) {
        phwangLogit("phwangDequeue", "null queue_val");
        return 0;
    }

    if (strcmp(((QueueMgrClass *) queue_val)->objectName(), "QueueMgrClass")) {
        phwangLogit("phwangDequeue", "wrong object");
        return 0;
    }

    return ((QueueMgrClass *) queue_val)->dequeueData();
}
