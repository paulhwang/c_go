/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "base_mgr_class.h"

void baseMgrReceiveDataFromTransport (void *base_mgr_object_val, void *data_val) {
    //phwangLogit("Golbal::baseMgrReceiveDataFromTransport", (char *) data_val);
    ((BaseMgrClass *) base_mgr_object_val)->exportedNetReceiveFunction((char *) data_val);
}

void BaseMgrClass::exportedNetReceiveFunction(char *data_val)
{
    this->logit("exportedNetReceiveFunction", data_val);
    if (data_val) {
        this->parseReceiveData(data_val);
    }
}

void BaseMgrClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, baseMgrReceiveDataFromTransport, this, this->objectName());
}
