/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_exports.cpp
*/

#include <string.h>
#include "utils_dir/queue_mgr_class.h"
#include "utils_dir/transport_class.h"
#include "root_dir/base_mgr_dir/base_mgr_class.h"
#include "main_class.h"

void mainReceiveDataFromTransport (void *main_object_val, void *data_val) {
    ((MainClass *) main_object_val)->exportRreceiveDataFromTransport(data_val);
}

void mainTransmitDataToTransport (void *main_object_val, void *data_val) {
    ((MainClass *) main_object_val)->exportTransmitDataToTransport(data_val);
}

void MainClass::exportRreceiveDataFromTransport (void *data_val) {
    char *game_name = (char *)"go";
    if (!strcmp(game_name, "go")) {
    	this->goBaseMgrObject->exportReceiveData(data_val);
    }
}

void MainClass::exportTransmitDataToTransport(void *data_val)
{
    this->logit("exportTransmitDataToTransport", (char *) data_val);
    this->transportObject->exportTransmitData(data_val);
}
