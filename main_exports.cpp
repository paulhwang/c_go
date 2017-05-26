/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_exports.cpp
*/

#include "utils_dir/queue_mgr_class.h"
#include "engine_class.h"

void receiveDataFromTransportFunc (void* main_object_val, void *data_val) {
    ((EngineClass *) main_object_val)->receiveDataFromTransport(data_val);
}
