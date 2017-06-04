/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "link_mgr_class.h"

void LinkMgrClass::exportReceiveData(void *data_val)
{
    phwangEnqueue(this->theReceiveQueue, data_val);
}

