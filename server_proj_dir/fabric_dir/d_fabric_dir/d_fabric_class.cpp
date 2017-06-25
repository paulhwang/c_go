/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_fabric_class.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "../fabric_class.h"
#include "../u_fabric_dir/u_fabric_class.h"

DFabricClass::DFabricClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(DFabricClass));
    this->theFabricObject = fabric_object_val;
    this->startNetServer();

    this->debug(true, "DFabricClass", "init");
}

DFabricClass::~DFabricClass (void)
{
}

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
    ((DFabricClass *) d_fabric_object_val)->exportedparseFunction((char *) data_val);
}

void DFabricClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, LINK_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, dFabricTpServerAcceptFunction, this, dFabricTpReceiveDataFunction, this, this->objectName());
}

void DFabricClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DFabricClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
