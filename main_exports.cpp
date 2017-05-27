/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_exports.cpp
*/

#include "utils_dir/queue_mgr_class.h"
#include "engine_class.h"

void mainReceiveDataFromTransport (void* main_object_val, void *data_val) {
    ((EngineClass *) main_object_val)->exportRreceiveDataFromTransport(data_val);
}

void mainTransmitDataToTransport (void* main_object_val, void *data_val) {
    ((EngineClass *) main_object_val)->exportTransmitDataToTransport(data_val);
}

void EngineClass::exportRreceiveDataFromTransport (void *data_val) {
    this->goReceiveQueue()->enqueueData(data_val);
}

void EngineClass::exportTransmitDataToTransport(void *data_val)
{
    this->logit("exportTransmitDataToTransport", (char *) data_val);
}
