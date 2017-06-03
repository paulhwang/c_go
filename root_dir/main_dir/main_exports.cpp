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
    ((BaseMgrClass *) main_object_val)->exportReceiveData(data_val);
}

void mainLinkMgrReceiveDataFromTransport (void *main_object_val, void *data_val) {
    LOGIT("Golbal::mainLinkMgrReceiveDataFromTransport", (char *) data_val);
    ((LinkMgrClass *) main_object_val)->exportReceiveData(data_val);
}

void mainBaseMgrTransmitDataToTransport (void *main_object_val, void *data_val) {
    ((MainClass *) main_object_val)->exportBaseMgrTransmitDataToTransport(data_val);
}

void mainLinkMgrTransmitDataToTransport (void *main_object_val, void *data_val) {
    ((MainClass *) main_object_val)->exportLinkMgrTransmitDataToTransport(data_val);
}

void MainClass::exportBaseMgrTransmitDataToTransport(void *data_val)
{
    this->logit("exportBaseMgrTransmitDataToTransport", (char *) data_val);
    this->theBaseMgrTpTransferObject->exportTransmitData(data_val);
}

void MainClass::exportLinkMgrTransmitDataToTransport(void *data_val)
{
    this->logit("exportLinkMgrTransmitDataToTransport", (char *) data_val);
    this->theLinkMgrTpTransferObject->exportTransmitData(data_val);
}
