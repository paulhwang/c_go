/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_root_class.cpp
*/

#include "../phwang.h"
#include "queue_root_class.h"
#include "queue_class.h"

QueueRootClass::QueueRootClass (void)
{
    memset(this, 0, sizeof (*this));
}

QueueRootClass::~QueueRootClass(void)
{
}

void *QueueRootClass::mallocQueue (int do_suspend_val, int max_size_val)
{
    QueueClass *queue = new QueueClass(do_suspend_val, max_size_val);
    return queue;
}

void QueueRootClass::freeQueue (void *queue_val)
{
    if (!queue_val) {
        this->abend("freeQueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        this->abend("freeQueue", "wrong object");
        return;
    }

    delete (QueueClass *) queue_val;
}

void QueueRootClass::enqueue (void *queue_val, void *data_val)
{
    if (!queue_val) {
        this->abend("enqueue", "null queue_val");
        return;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        this->abend("enqueue", "wrong object");
        return;
    }

    ((QueueClass *) queue_val)->enqueueData(data_val);
}

void *QueueRootClass::dequeue (void *queue_val)
{
    if (!queue_val) {
        this->abend("dequeue", "null queue_val");
        return 0;
    }

    if (strcmp(((QueueClass *) queue_val)->objectName(), "QueueClass")) {
        this->abend("dequeue", "wrong object");
        return 0;
    }

    return ((QueueClass *) queue_val)->dequeueData();
}

void QueueRootClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", ObjectName, str0_val);
    phwangLogit(s, str1_val);
}

void QueueRootClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", ObjectName, str0_val);
    phwangAbend(s, str1_val);
}
