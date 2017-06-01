/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_mgr_class.h
*/

#pragma once

#include <pthread.h>
#include "logit.h"
class QueueEntryClass;
class SuspendClass;

class QueueMgrClass
{
  //enum GETAC_MARKER_DEFINE_ marker_head;

    int theQueueSize;
    QueueEntryClass *queue_head;
    QueueEntryClass *queue_tail;
    int max_queue_size;
    SuspendClass *suspendObject;
    pthread_mutex_t *theMutex;
  //CRITICAL_SECTION cs_queue;
    int in_index;
    int out_index;

    void enqueueEntry(QueueEntryClass *entry);
    QueueEntryClass *dequeueEntry(void);
    int queueSize(void) {return this->theQueueSize;}
    int inIndex(void) {return in_index;}
    int outIndex(void) {return out_index;}

    void check_queue_error(void);
    void flush_queue(void);
    void delete_entry(QueueEntryClass *del_entry);

    void logit (char const* str0_val, char const* str1_val) {LOGIT(str0_val, str1_val);}
    void abend (char const* str0_val, char const* str1_val) {ABEND(str0_val, str1_val);}

public:
    QueueMgrClass(void);
    ~QueueMgrClass(void);

    void initQueue(int max_queue_size_val);
    void enqueueData(void *data_val);
    void *dequeueData(void);

  /* always at the tail of this class */
  //enum GETAC_MARKER_DEFINE_ marker_tail;
};
