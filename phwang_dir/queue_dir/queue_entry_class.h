/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_entry_class.h
*/

#pragma once

class QueueEntryClass
{
  friend class QueueClass;

  QueueEntryClass *next;
  QueueEntryClass *prev;
  void *data;

  void deleteQueueEntry(void);

public:
  QueueEntryClass(void);
  ~QueueEntryClass(void);
};
