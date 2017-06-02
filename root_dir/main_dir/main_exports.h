/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_exports.h
*/

void mainReceiveDataFromTransport(void *main_object_val, void *data_val);
void mainBaseMgrReceiveDataFromTransport(void *main_object_val, void *data_val);
void mainLinkMgrReceiveDataFromTransport(void *main_object_val, void *data_val);
void mainTransmitDataToTransport(void* main_object_val, void *data_val);
