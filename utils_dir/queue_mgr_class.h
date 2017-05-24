/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_mgr_class.h
*/

#pragma once

class getac_que_ent;

class getac_que_mgr
{
  //enum GETAC_MARKER_DEFINE_ marker_head;

  int queue_size;
  getac_que_ent *queue_head;
  getac_que_ent *queue_tail;
  int max_queue_size;
  //CRITICAL_SECTION cs_queue;
  int in_index;
  int out_index;

  void check_queue_error(void);
  void flush_queue(void);
  void delete_entry(getac_que_ent *del_entry);

public:
  getac_que_mgr(void);
  ~getac_que_mgr(void);

  void init_queue(int max_queue_size_val);
  void enqueue_entry(getac_que_ent *entry);
  getac_que_ent *dequeue_entry(void);
  int queue_size_(void) {return queue_size;}
  int in_index_(void) {return in_index;}
  int out_index_(void) {return out_index;}

  /* always at the tail of this class */
  //enum GETAC_MARKER_DEFINE_ marker_tail;
};
