/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_queue.cpp
*/

#include "../phwang.h"
#include "../queue_dir/queue_class.h"
#include "phwang_class.h"

void *PhwangClass::mallocQueue (int max_size_val)
{
    QueueClass *queue = new QueueClass(max_size_val);
    return queue;
}

void PhwangClass::freeQueue (void *queue_val)
{
    if (!queue_val) {
        phwangAbend("phwangFreeQueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbend("phwangFreeQueue", "wrong object");
        return;
    }

    ((QueueClass *) queue_val)->~QueueClass();
}

void PhwangClass::enqueue (void *queue_val, void *data_val)
{
    if (!queue_val) {
        phwangAbend("phwangEnqueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbend("phwangEnqueue", "wrong object");
        return;
    }

    ((QueueClass *) queue_val)->enqueueData(data_val);
}

void *PhwangClass::dequeue (void *queue_val)
{
    if (!queue_val) {
        phwangAbend("phwangDequeue", "null queue_val");
        return 0;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbend("phwangDequeue", "wrong object");
        return 0;
    }

    return ((QueueClass *) queue_val)->dequeueData();
}
