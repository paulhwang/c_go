/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_export.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "base_mgr_class.h"

void baseMgrReceiveDataFromTransport (void *base_mgr_object_val, void *data_val);

void BaseMgrClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, baseMgrReceiveDataFromTransport, this);
}

void BaseMgrClass::exportAcceptConnection (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
    //phwangLogit("exportAcceptConnection", this->theTpTransferObject->objectName());
}



