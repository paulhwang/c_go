/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.cpp
*/

#include "../../utils_dir/queue_dir/queue_class.h"
#include "link_mgr_class.h"

void LinkMgrClass::exportReceiveData(void *data_val)
{
    this->theReceiveQueue->enqueueData(data_val);
}

