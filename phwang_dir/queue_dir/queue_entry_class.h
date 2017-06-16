/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_entry_class.h
*/

#pragma once

class QueueEntryClass
{
/***************************************************************/
/* DO NOT ADD FRIEND INTO THIS CLASS UNLESS YOU GET PERMISSION */
  friend class QueueClass;
/* DO NOT ADD FRIEND INTO THIS CLASS UNLESS YOU GET PERMISSION */
/***************************************************************/

  //enum GETAC_MARKER_DEFINE_ marker_head;

  QueueEntryClass *next;
  QueueEntryClass *prev;

  void deleteQueueEntry(void);

  void *data;

public:
  QueueEntryClass(void);
  ~QueueEntryClass(void);
};
