/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_export.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "base_mgr_class.h"

void baseMgrTransportServerAcceptConnection (void *base_mgr_object_val, void *tp_transfer_object_val) {
    //phwangLogit("Golbal::baseMgrTransportServerAcceptConnection", "");
    ((BaseMgrClass *) base_mgr_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void BaseMgrClass::exportedNetAcceptFunction (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
}

void baseMgrReceiveDataFromTransport (void *base_mgr_object_val, void *data_val) {
    //phwangLogit("Golbal::baseMgrReceiveDataFromTransport", (char *) data_val);
    ((BaseMgrClass *) base_mgr_object_val)->exportedNetReceiveFunction(data_val);
}

void BaseMgrClass::exportedNetReceiveFunction(void *data_val)
{
    this->logit("exportedNetReceiveFunction", (char *) data_val);
    phwangEnqueue(this->theReceiveQueue, data_val);
}

void BaseMgrClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER1, baseMgrTransportServerAcceptConnection, this, baseMgrReceiveDataFromTransport, this, this->objectName());
}

void BaseMgrClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, baseMgrReceiveDataFromTransport, this, this->objectName());
}
