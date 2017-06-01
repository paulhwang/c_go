/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_mgr_class.cpp
*/

#include <string.h>
#include <stdlib.h>
//#include "stdafx.h"
//#include "getac_aggr_include.h"/* Put this file immediately after stdafx.h */
//#include "mitac_rfid_engine_common_include.h"
#include "queue_mgr_class.h"
#include "queue_entry_class.h"
#include "suspend_class.h"
//#include "getac_def_component.h"
//#include "getac_def_marker.h"

QueueMgrClass::QueueMgrClass(void)
{
    memset(this, 0, sizeof(*this));
    this->suspendObject = new SuspendClass();
    this->theMutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(this->theMutex, NULL);

    //this->marker_head = this->marker_tail = GETAC_MARKER_UTIL_QUE_ENT;
}

QueueMgrClass::~QueueMgrClass(void)
{
    if (this->theQueueSize) {
        //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    }
    delete this->suspendObject;
    free(this->theMutex);
}

void QueueMgrClass::initQueue(int max_queue_size_val)
{
  max_queue_size = max_queue_size_val;
  //InitializeCriticalSectionAndSpinCount(&cs_queue, 0);
}

void QueueMgrClass::enqueueData (void *data_val)
{
    if (1) {
        this->logit("enqueueData", (char *) data_val);
    }

    QueueEntryClass *entry = new QueueEntryClass();
    if (!entry) {
        this->abend("enqueueData", "fail to create new QueueEntryClass");
        return;
    }
    else {
        entry->data = data_val;
    }
    this->enqueueEntry(entry);
    this->suspendObject->signal();
}

void *QueueMgrClass::dequeueData (void)
{
    while (1) {
        QueueEntryClass *entry = this->dequeueEntry();
        if (entry) {
            void *data = entry->data;
            this->delete_entry(entry);

            if (1) {
                this->logit("dequeueData", (char *) data);
            }
            return data;
        }
        else {
            this->suspendObject->wait();
        }
    }
}

void QueueMgrClass::enqueueEntry(QueueEntryClass *entry)
{
  if (!this) {
    //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    return;
  }
 
  if (!entry) {
    //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    return;
  }

  /* queue is too big */
  if (max_queue_size && max_queue_size && (this->theQueueSize > max_queue_size)) {
    delete_entry(entry);
    //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    return;
  }
    
    entry->next = 0;  
    pthread_mutex_lock(this->theMutex);
    in_index++;

    if (!this->theQueueHead) {
        entry->prev = 0;
        this->theQueueHead = entry;
        this->theQueueTail = entry;
        this->theQueueSize = 1; 
    }
    else {        
        entry->prev = this->theQueueTail;
        this->theQueueTail->next = entry;
        this->theQueueTail = entry;
        this->theQueueSize++;
    }
    pthread_mutex_unlock(this->theMutex);
}

QueueEntryClass *QueueMgrClass::dequeueEntry(void)
{
    QueueEntryClass *entry;

    if (!this->theQueueHead) {
        return 0;
    }

    out_index = in_index;
    pthread_mutex_lock(this->theMutex);

    if (this->theQueueSize == 1) {
        entry = this->theQueueHead;
        this->theQueueHead = this->theQueueTail = 0;
        this->theQueueSize = 0;
        pthread_mutex_unlock(this->theMutex);
        return entry;
    }

    entry = this->theQueueHead;
    this->theQueueHead = this->theQueueHead->next;
    this->theQueueHead->prev = 0;
    this->theQueueSize--;
    pthread_mutex_unlock(this->theMutex);
    return entry;
}

void QueueMgrClass::check_queue_error(void)
{
#if MITAC_RFID_DEBUG_HEAP
    QueueEntryClass *entry;
    int length = 0;
 
    if (!this) {
        return;
    }
 
    pthread_mutex_lock(this->theMutex);
    entry = this->theQueueHead;
    while (entry) {
        length++;
        entry = entry->next;
    }
 
    if (length != queue_size) {
        abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    }

    pthread_mutex_unlock(this->theMutex);
#endif
}

void QueueMgrClass::flush_queue(void)
{
    QueueEntryClass *entry, *entry_next; 
 
    pthread_mutex_lock(this->theMutex);
    entry = this->theQueueHead;
    while (entry) {
        entry_next = entry->next;
        delete_entry(entry);
        this->theQueueSize--;
        entry = entry_next;
    }
    this->theQueueHead = this->theQueueTail = 0;
 
    if (this->theQueueSize) {
        //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    }

    pthread_mutex_unlock(this->theMutex);
}

void QueueMgrClass::delete_entry(QueueEntryClass *del_entry)
{
    delete del_entry;
}
