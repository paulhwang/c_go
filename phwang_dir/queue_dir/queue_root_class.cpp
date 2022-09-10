/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_root_class.cpp
*/

#include "../phwang.h"
#include "queue_root_class.h"
#include "queue_class.h"

QueueRootClass::QueueRootClass (int debug_code_val)
{
    memset(this, 0, sizeof (*this));
    this->theDebugCode = debug_code_val;
}

QueueRootClass::~QueueRootClass(void)
{
}

void *QueueRootClass::mallocQueue (int do_suspend_val, int max_size_val, char const *who_val)
{
    QueueClass *queue = new QueueClass(do_suspend_val, max_size_val, who_val);
    this->theNumberOfQueue++;
    return queue;
}

void QueueRootClass::freeQueue (void *queue_val)
{
    if (!queue_val) {
        phwangAbendS("QueueRootClass::freeQueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbendS("QueueRootClass::freeQueue", "wrong object");
        return;
    }

    this->theNumberOfQueue--;
    delete (QueueClass *) queue_val;
}

int QueueRootClass::enqueue (void *queue_val, void *data_val)
{
    if (!queue_val) {
        phwangAbendS("QueueRootClass::enqueue", "null queue_val");
        return QueueClass::ENQUEUE_NULL;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbendS("QueueRootClass::enqueue", "wrong object");
        return QueueClass::ENQUEUE_INVALID_CLASS;
    }

    return ((QueueClass *) queue_val)->enqueueData(data_val);
}

void *QueueRootClass::dequeue (void *queue_val)
{
    if (!queue_val) {
        phwangAbendS("QueueRootClass::dequeue", "null queue_val");
        return 0;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        phwangAbendS("QueueRootClass::dequeue", "wrong object");
        return 0;
    }

    return ((QueueClass *) queue_val)->dequeueData();
}
