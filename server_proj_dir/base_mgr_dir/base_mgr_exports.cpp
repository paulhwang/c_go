/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_export.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "base_mgr_class.h"
#include "../protocol_dir/net_port_protocol.h"

void baseMgrReceiveDataFromTransport (void *base_mgr_object_val, void *data_val) {
    //phwangLogit("Golbal::baseMgrReceiveDataFromTransport", (char *) data_val);
    ((BaseMgrClass *) base_mgr_object_val)->exportedNetReceiveFunction(data_val);
}

void BaseMgrClass::exportedNetReceiveFunction(void *data_val)
{
    this->logit("exportedNetReceiveFunction", (char *) data_val);
    phwangEnqueue(this->theReceiveQueue, data_val);
}

void BaseMgrClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, baseMgrReceiveDataFromTransport, this, this->objectName());
}
