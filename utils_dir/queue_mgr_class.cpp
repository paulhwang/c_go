/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_mgr_class.cpp
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
    this->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(this->mutex, NULL);

    //this->marker_head = this->marker_tail = GETAC_MARKER_UTIL_QUE_ENT;
}

QueueMgrClass::~QueueMgrClass(void)
{
    if (this->queue_size) {
        //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    }
    delete this->suspendObject;
    free(this->mutex);
}

void QueueMgrClass::initQueue(int max_queue_size_val)
{
  max_queue_size = max_queue_size_val;
  //InitializeCriticalSectionAndSpinCount(&cs_queue, 0);
}

void QueueMgrClass::enqueueData (void *data_val)
{
    if (0) {
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

            if (0) {
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
  if (max_queue_size && max_queue_size && (queue_size > max_queue_size)) {
    delete_entry(entry);
    //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    return;
  }
    
  entry->next = 0;  
  //EnterCriticalSection(&cs_queue);
  in_index++;

  if (!queue_head) {
    entry->prev = 0;
    queue_head = entry;
    queue_tail = entry;
    queue_size = 1; 
  }
  else {        
    entry->prev = queue_tail;
    queue_tail->next = entry;
    queue_tail = entry;
    queue_size++;
  }

  //LeaveCriticalSection(&cs_queue);
}

QueueEntryClass *QueueMgrClass::dequeueEntry(void)
{
  QueueEntryClass *entry;

  if (!this->queue_head) {
    return 0;
  }

  out_index = in_index;

  //EnterCriticalSection(&cs_queue);


  if (queue_size == 1) {
    entry = queue_head;
    queue_head = queue_tail = 0;
    queue_size = 0;
    //LeaveCriticalSection(&cs_queue);
    return entry;
  }

  entry = queue_head;
  queue_head = queue_head->next;
  queue_head->prev = 0;
  queue_size--;
  //LeaveCriticalSection(&cs_queue);
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
 
  //EnterCriticalSection(&cs_queue);
  entry = queue_head;
  while (entry) {
    length++;
    entry = entry->next;
  }
 
  if (length != queue_size) {
    abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
  }

  //LeaveCriticalSection(&cs_queue);
#endif
}

void QueueMgrClass::flush_queue(void)
{
  QueueEntryClass *entry, *entry_next; 
 
  //EnterCriticalSection(&cs_queue);
  entry = queue_head;
  while (entry) {
    entry_next = entry->next;
    delete_entry(entry);
    queue_size--;
    entry = entry_next;
  }
  queue_head = queue_tail = 0;
 
  if (queue_size) {
    //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
  }

  //LeaveCriticalSection(&cs_queue);
}

void QueueMgrClass::delete_entry(QueueEntryClass *del_entry)
{
    delete del_entry;
}
