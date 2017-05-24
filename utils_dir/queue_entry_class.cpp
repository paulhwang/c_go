/*
  Copyrights reserved
  Written by Paul Hwang
  File name:queue_entry_class.cpp
*/

//#include "stdafx.h"
//#include "getac_aggr_include.h"/* Put this file immediately after stdafx.h */
//#include "mitac_rfid_engine_common_include.h"
#include "queue_entry_class.h"
//#include "getac_def_component.h"
//#include "getac_def_marker.h"

getac_que_ent::getac_que_ent(void)
{
  //this->marker_head = GETAC_MARKER_UTIL_QUE_MGR;
  this->data = 0;
}

getac_que_ent::~getac_que_ent(void)
{
}

void getac_que_ent::delete_queue_entry(void)
{
  if (!this) {
    //abend(GATEWAY_LOG_TYPE_RFID, MTC_ERR_MISC, __LINE__, __FUNCTION__);
    return;
  }

  delete this;
}
