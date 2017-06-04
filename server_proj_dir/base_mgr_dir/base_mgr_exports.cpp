/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_export.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "base_mgr_class.h"

void BaseMgrClass::exportReceiveData(void *data_val)
{
    phwangEnqueue(this->theReceiveQueue, data_val);
}

