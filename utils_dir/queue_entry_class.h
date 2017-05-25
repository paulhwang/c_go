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
  friend class QueueMgrClass;
/* DO NOT ADD FRIEND INTO THIS CLASS UNLESS YOU GET PERMISSION */
/***************************************************************/

  //enum GETAC_MARKER_DEFINE_ marker_head;

  QueueEntryClass *next;
  QueueEntryClass *prev;

public:
  QueueEntryClass(void);
  ~QueueEntryClass(void);

  void deleteQueueEntry(void);

  void *data;
};
