/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_entry_class.h
*/

#pragma once

class getac_que_ent
{
/***************************************************************/
/* DO NOT ADD FRIEND INTO THIS CLASS UNLESS YOU GET PERMISSION */
  friend class getac_que_mgr;
/* DO NOT ADD FRIEND INTO THIS CLASS UNLESS YOU GET PERMISSION */
/***************************************************************/

  //enum GETAC_MARKER_DEFINE_ marker_head;

  getac_que_ent *next;
  getac_que_ent *prev;

public:
  getac_que_ent(void);
  ~getac_que_ent(void);

  void delete_queue_entry(void);

  void *data;
};
