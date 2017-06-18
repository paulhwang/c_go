/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_fabric_class.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "../fabric_class.h"
#include "../u_fabric_dir/u_fabric_class.h"
#include "../link_mgr_dir/link_mgr_class.h"

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
    ((DFabricClass *) d_fabric_object_val)->exportedNetReceiveFunction((char *) data_val);
}

void DFabricClass::exportedNetReceiveFunction(char *data_val)
{
    this->logit("receiveFunction", data_val);

    if (*data_val == LINK_MGR_PROTOCOL_COMMAND_IS_MALLOC_LINK) {
        data_val++;
        this->theFabricObject->linkMgrObject()->mallocLink(data_val);
    }
    else if (*data_val == LINK_MGR_PROTOCOL_COMMAND_IS_MALLOC_SESSION) {
        data_val++;
        this->theFabricObject->linkMgrObject()->mallocSession(data_val);
    }
    else if (*data_val == LINK_MGR_PROTOCOL_COMMAND_IS_PUT_SESSION_DATA) {
        data_val++;
        this->theFabricObject->linkMgrObject()->putSessionData(data_val);
    }

    //this->theFabricObject->uFabricObject()->transmitFunction(data_val);
}

void DFabricClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, LINK_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, dFabricTpServerAcceptFunction, this, dFabricTpReceiveDataFunction, this, this->objectName());
}
