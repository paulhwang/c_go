/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.cpp
*/

#include "../../utils_dir/queue_mgr_class.h"
#include "base_mgr_class.h"

void BaseMgrClass::exportReceiveData(void *data_val)
{
    char *data = (char *) data_val;

    if (*data == 'm') {

    }
    else if (*data == 'd') {
        this->receiveQueue->enqueueData(data + 1);
    }
    else {
    }
}

