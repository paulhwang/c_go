/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_root_class.h
*/

#pragma once

class QueueRootClass
{
    char const *objectName(void) {return "QueueRootClass";}
    int theDebugCode;
    int theNumberOfQueue;

public:
    QueueRootClass(int debug_code_val);
    ~QueueRootClass(void);

    int numberOfQueueb(void) {return this->theNumberOfQueue;}
    void *mallocQueue(
        int debug_on_val,
        int do_suspend_val,
        int max_size_val,
        char const *who_val);
    void freeQueue(void *queue_val);
    int enqueue(void *queue_val, void *data_val);
    void *dequeue(void *queue_val);
};
