/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_entry_class.cpp
*/

#include "../phwang.h"
//#include "stdafx.h"
//#include "getac_aggr_include.h"/* Put this file immediately after stdafx.h */
//#include "mitac_rfid_engine_common_include.h"
#include "queue_entry_class.h"
//#include "getac_def_component.h"
//#include "getac_def_marker.h"

QueueEntryClass::QueueEntryClass(void)
{
  //this->marker_head = GETAC_MARKER_UTIL_QUE_MGR;
    memset((char *) this, 0, sizeof (QueueEntryClass));
}

QueueEntryClass::~QueueEntryClass(void)
{
}

void QueueEntryClass::deleteQueueEntry(void)
{
  if (!this) {
    //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    return;
  }

  delete this;
}
