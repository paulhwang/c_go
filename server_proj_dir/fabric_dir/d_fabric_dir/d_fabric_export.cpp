/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_fabric_class.h"

void dFabricTpServerAcceptFunction (void *d_fabric_object_val, void *tp_transfer_object_val) {
    phwangLogit("Golbal::dFabricTpServerAcceptFunction", "");
    ((DFabricClass *) d_fabric_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void DFabricClass::exportedNetAcceptFunction (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
}

void dFabricTpReceiveDataFunction (void *d_fabric_object_val, void *data_val) {
    phwangLogit("Golbal::dFabricTpReceiveDataFunction", (char *) data_val);
    ((DFabricClass *) d_fabric_object_val)->exportedNetReceiveFunction(data_val);
}

void DFabricClass::exportedNetReceiveFunction(void *data_val)
{
    phwangEnqueue(this->theReceiveQueue, data_val);
}

void DFabricClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, LINK_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, dFabricTpServerAcceptFunction, this, dFabricTpReceiveDataFunction, this);
}
