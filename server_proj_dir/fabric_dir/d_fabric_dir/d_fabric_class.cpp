/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_class.cpp
*/

#include <sys/socket.h>
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../../phwang_dir/abend_dir/abend_class.h"
#include "../../define_dir/tcp_port_define.h"
#include "../../define_dir/fe_def.h"
#include "d_fabric_class.h"
#include "../fabric_class.h"
#include "../u_fabric_dir/u_fabric_class.h"

DFabricClass::DFabricClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(DFabricClass));

    this->theFabricObject = fabric_object_val;
    this->setTimeStampString();
    this->startNetServer();

    phwangDebugS(false, "DFabricClass::DFabricClass", "init");
}

DFabricClass::~DFabricClass (void)
{
}

void dFabricTpServerAcceptFunction (void *d_fabric_object_val, void *tp_transfer_object_val) {
    if (!tp_transfer_object_val) {
        phwangAbendS("Golbal::dFabricTpServerAcceptFunction", "null tp_transfer_object_val");
    }

    ((DFabricClass *) d_fabric_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void DFabricClass::exportedNetAcceptFunction (void *tp_transfer_object_val)
{
    if (!tp_transfer_object_val) {
        phwangAbendS("DFabricClass::exportedNetAcceptFunction", "null tp_transfer_object_val");
        return;
    }
    this->theTpTransferObject = tp_transfer_object_val;

    char *buf = (char *) phwangMalloc(strlen(this->timeStampString()) + 1, MallocClass::TCP_ACCEPT_CALLBACK_FUNC);
    strcpy(buf, this->timeStampString());
    phwangTpTransmit(tp_transfer_object_val, buf);
}

void dFabricTpReceiveDataFunction (void *tp_transfer_object_val, void *d_fabric_object_val, void *data_val) {
    char *data_str_val = (char *) data_val;
    if (data_str_val[1] != FE_CommandClass::GET_LINK_DATA_COMMAND) {
        phwangDebugSSI(true, "Golbal::dFabricTpReceiveDataFunction", (char *) data_val, "index", phwangGetPortObjectIndex(tp_transfer_object_val));
    }

    ((DFabricClass *) d_fabric_object_val)->exportedParseFunction(tp_transfer_object_val, (char *) data_val);
    phwangFree(data_val);
}

void DFabricClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, TcpPortDefine::FABRIC_NODEJS_PORT_NUMER, dFabricTpServerAcceptFunction, this, dFabricTpReceiveDataFunction, this, this->objectName());
}

void DFabricClass::setTimeStampString (void)
{
    time_t seconds = time(NULL);
    int time_stamp = (int) ((seconds - 1642858200) / 60);
    phwangEncodeNumber(this->theTimeStampString, time_stamp, FABRIC_SERVER_TIME_STAMP_LENGTH_SIZE);
    phwangDebugS(false, "DFabricClass::setTimeStampString", this->timeStampString());
}
