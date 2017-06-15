/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_fabric_class.h"
#include "../../protocol_dir/game_server_protocol.h"

void uFabricTpServerAcceptFunction (void *u_fabric_object_val, void *tp_transfer_object_val) {
    phwangLogit("Golbal::uFabricTpServerAcceptFunction", "");
    ((UFabricClass *) u_fabric_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void UFabricClass::exportedNetAcceptFunction (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
}

void uFabricTpReceiveDataFunction (void *u_fabric_object_val, void *data_val) {
    phwangLogit("Golbal::uFabricTpReceiveDataFunction", (char *) data_val);
    ((UFabricClass *) u_fabric_object_val)->exportedNetReceiveFunction(data_val);
}

void UFabricClass::exportedNetReceiveFunction(void *data_val)
{
    phwangEnqueue(this->theReceiveQueue, data_val);
}

void UFabricClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, GAME_SERVER_PROTOCOL_TRANSPORT_PORT_NUMBER, uFabricTpServerAcceptFunction, this, uFabricTpReceiveDataFunction, this, this->objectName());
}
