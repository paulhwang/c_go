/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_exports.cpp
*/

#include "engine_class.h"

void receiveDataFromTransportFunc (void* main_object_val, void *data_val) {
    ((EngineClass *) main_object_val)->receiveDataFromTransport(data_val);
}
