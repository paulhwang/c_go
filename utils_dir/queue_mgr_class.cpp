/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_mgr_class.cpp
*/

#include <string.h>
//#include "stdafx.h"
//#include "getac_aggr_include.h"/* Put this file immediately after stdafx.h */
//#include "mitac_rfid_engine_common_include.h"
#include "queue_mgr_class.h"
#include "queue_entry_class.h"
//#include "getac_def_component.h"
//#include "getac_def_marker.h"

getac_que_mgr::getac_que_mgr(void)
{
  memset(this, 0, sizeof(*this));
  //this->marker_head = this->marker_tail = GETAC_MARKER_UTIL_QUE_ENT;
}

getac_que_mgr::~getac_que_mgr(void)
{
  if (this->queue_size) {
    //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
  }
}

void getac_que_mgr::init_queue(int max_queue_size_val)
{
  max_queue_size = max_queue_size_val;
  //InitializeCriticalSectionAndSpinCount(&cs_queue, 0);
}

void getac_que_mgr::enqueue_entry(getac_que_ent *entry)
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

getac_que_ent *getac_que_mgr::dequeue_entry(void)
{
  getac_que_ent *entry;

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

void getac_que_mgr::check_queue_error(void)
{
#if MITAC_RFID_DEBUG_HEAP
  getac_que_ent *entry;
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

void getac_que_mgr::flush_queue(void)
{
  getac_que_ent *entry, *entry_next; 
 
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

void getac_que_mgr::delete_entry(getac_que_ent *del_entry)
{
  delete del_entry;
}
