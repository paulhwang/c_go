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
#include "../link_mgr_dir/link_mgr_class.h"
#include "main_class.h"

void mainBaseMgrReceiveDataFromTransport (void *main_object_val, void *data_val) {
    LOGIT("Golbal::mainBaseMgrReceiveDataFromTransport", (char *) data_val);
    ((MainClass *) main_object_val)->exportBaseMgrReceiveDataFromTransport(data_val);
}

void mainLinkMgrReceiveDataFromTransport (void *main_object_val, void *data_val) {
    LOGIT("Golbal::mainLinkMgrReceiveDataFromTransport", (char *) data_val);
    ((MainClass *) main_object_val)->exportLinkMgrReceiveDataFromTransport(data_val);
}

void mainTransmitDataToTransport (void *main_object_val, void *data_val) {
    ((MainClass *) main_object_val)->exportTransmitDataToTransport(data_val);
}

void MainClass::exportBaseMgrReceiveDataFromTransport (void *data_val) {
    char *game_name = (char *)"go";
    if (!strcmp(game_name, "go")) {
        this->logit("exportBaseMgrReceiveDataFromTransport", (char *) data_val);
        this->theGoBaseMgrObject->exportReceiveData(data_val);
    }
}

void MainClass::exportLinkMgrReceiveDataFromTransport (void *data_val) {
    this->logit("exportLinkMgrReceiveDataFromTransport", (char *) data_val);
    this->theLinkMgrObject->exportReceiveData(data_val);
}

void MainClass::exportTransmitDataToTransport(void *data_val)
{
    this->logit("exportTransmitDataToTransport", (char *) data_val);
    this->theBaseMgrTpTransferObject->exportTransmitData(data_val);
}
