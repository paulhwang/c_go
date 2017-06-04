/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue.cpp
*/

#include "../phwang.h"
#include "queue_class.h"

void *phwangMallocQueue (int size_val)
{
    QueueClass *queue = new QueueClass();
    return queue;
}

void phwangFreeQueue (void *queue_val)
{
    if (!queue_val) {
        phwangLogit("phwangFreeQueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangLogit("phwangFreeQueue", "wrong object");
        return;
    }

    ((QueueClass *) queue_val)->~QueueClass();
}

void phwangEnqueue (void *queue_val, void *data_val)
{
    if (!queue_val) {
        phwangLogit("phwangEnqueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangLogit("phwangEnqueue", "wrong object");
        return;
    }

    ((QueueClass *) queue_val)->enqueueData(data_val);
}

void *phwangDequeue (void *queue_val)
{
    if (!queue_val) {
        phwangLogit("phwangDequeue", "null queue_val");
        return 0;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangLogit("phwangDequeue", "wrong object");
        return 0;
    }

    return ((QueueClass *) queue_val)->dequeueData();
}
