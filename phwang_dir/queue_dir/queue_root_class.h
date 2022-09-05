/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_root_class.h
*/

#pragma once

class QueueRootClass
{
    char const *objectName(void) {return "QueueRootClass";}

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    QueueRootClass(void);
    ~QueueRootClass(void);

    void *mallocQueue(int do_suspend_val, int max_size_val);
    void freeQueue(void *queue_val);
    void enqueue(void *queue_val, void *data_val);
    void *dequeue(void *queue_val);
};
