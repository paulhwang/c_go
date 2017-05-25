/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_mgr_class.h
*/

#pragma once

class QueueEntryClass;

class QueueMgrClass
{
  //enum GETAC_MARKER_DEFINE_ marker_head;

  int queue_size;
  QueueEntryClass *queue_head;
  QueueEntryClass *queue_tail;
  int max_queue_size;
  //CRITICAL_SECTION cs_queue;
  int in_index;
  int out_index;

  void check_queue_error(void);
  void flush_queue(void);
  void delete_entry(QueueEntryClass *del_entry);

public:
  QueueMgrClass(void);
  ~QueueMgrClass(void);

  void initQueue(int max_queue_size_val);
  void enqueueEntry(QueueEntryClass *entry);
  QueueEntryClass *dequeueEntry(void);
  int queueSize(void) {return queue_size;}
  int inIndex(void) {return in_index;}
  int outIndex(void) {return out_index;}

  /* always at the tail of this class */
  //enum GETAC_MARKER_DEFINE_ marker_tail;
};
