/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_exports.h
*/

void mainBaseMgrReceiveDataFromTransport(void *main_object_val, void *data_val);
void mainBaseMgrTransmitDataToTransport(void* main_object_val, void *data_val);

void mainLinkMgrReceiveDataFromTransport(void *main_object_val, void *data_val);
void mainLinkMgrTransmitDataToTransport(void* main_object_val, void *data_val);
