/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_exports.cpp
*/

#include <string.h>
#include "../../utils_dir/queue_mgr_class.h"
#include "../tp_dir/tp_class.h"
#include "../tp_dir/tp_transfer_class.h"
#include "../base_mgr_dir/base_mgr_class.h"
#include "main_class.h"

void mainBaseMgrReceiveDataFromTransport (void *main_object_val, void *data_val) {
    ((MainClass *) main_object_val)->exportBaseMgrRreceiveDataFromTransport(data_val);
}

void mainLinkMgrReceiveDataFromTransport (void *main_object_val, void *data_val) {
    ((MainClass *) main_object_val)->exportLinkMgrRreceiveDataFromTransport(data_val);
}

void mainTransmitDataToTransport (void *main_object_val, void *data_val) {
    ((MainClass *) main_object_val)->exportTransmitDataToTransport(data_val);
}

void MainClass::exportBaseMgrRreceiveDataFromTransport (void *data_val) {
    char *game_name = (char *)"go";
    if (!strcmp(game_name, "go")) {
        this->logit("exportBaseMgrRreceiveDataFromTransport", (char *) data_val);
        this->theGoBaseMgrObject->exportReceiveData(data_val);
    }
}

void MainClass::exportLinkMgrRreceiveDataFromTransport (void *data_val) {
    char *game_name = (char *)"go";
    if (!strcmp(game_name, "go")) {
        this->logit("exportLinkMgrRreceiveDataFromTransport", (char *) data_val);
        this->theGoBaseMgrObject->exportReceiveData(data_val);
    }
}

void MainClass::exportTransmitDataToTransport(void *data_val)
{
    this->logit("exportTransmitDataToTransport", (char *) data_val);
    this->theBaseMgrTpTransferObject->exportTransmitData(data_val);
}
