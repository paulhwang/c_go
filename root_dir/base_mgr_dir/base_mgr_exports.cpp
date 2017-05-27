/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.cpp
*/

#include "../../utils_dir/queue_mgr_class.h"
#include "base_mgr_class.h"

void BaseMgrClass::exportReceiveData(void *data_val)
{
    this->receiveQueue->enqueueData(data_val);

}

