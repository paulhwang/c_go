/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.cpp
*/

#include "../../utils_dir/queue_mgr_class.h"
#include "link_mgr_class.h"

void LinkMgrClass::exportReceiveData(void *data_val)
{
    this->receiveQueue->enqueueData(data_val);
}

