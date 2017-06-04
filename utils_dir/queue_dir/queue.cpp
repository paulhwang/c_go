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

void phwangEnqueue (void *queue_val, void *data)
{
    if (!queue_val) {
        return;
    }
    if (!strcmp(((QueueMgrClass *) queue_val)->objectName(), "QueueMgrClass")) {
        return;
    }
}

void *phwangDequeue (void *queue_val)
{
    if (!queue_val) {
        return 0;
    }

}
