/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_class.cpp
*/

#include <sys/socket.h>
#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../define_dir/tcp_port_define.h"
#include "../../define_dir/fe_def.h"
#include "d_fabric_class.h"
#include "../fabric_class.h"
#include "../u_fabric_dir/u_fabric_class.h"

DFabricClass::DFabricClass (int debug_on_val, FabricClass *fabric_obj_val)
{
    memset(this, 0, sizeof(DFabricClass));
    this->debugOn_ = true && debug_on_val;

    this->fabricObj_ = fabric_obj_val;
    this->setTimeStampString();
    this->startNetServer();

    phwangDebugS(false, "DFabricClass::DFabricClass", "init");
}

DFabricClass::~DFabricClass (void)
{
}

void dFabricTcoAcceptFunc (void *d_fabric_object_val, void *port_object_val) {
    if (!port_object_val) {
        phwangAbendS("Golbal::dFabricTcoAcceptFunc", "null port_object_val");
    }

    ((DFabricClass *) d_fabric_object_val)->tcpAccept(port_object_val);
}

void DFabricClass::tcpAccept (void *port_obj_val)
{
    if (!port_obj_val) {
        phwangAbendS("DFabricClass::tcpAccept", "null port_obj_val");
        return;
    }
    this->portObj_ = port_obj_val;

    char *time_stamp_buf =  (char *) phwangMalloc(SIZE_DEF::FABRIC_TIME_STAMP_SIZE + 1, MallocClass::exportedNetAcceptFunction);
    strcpy(time_stamp_buf, this->timeStampString_);
    phwangPortTransmit(port_obj_val, time_stamp_buf);
}

void dFabricTpReceiveDataFunction (void *port_obj_val, void *d_fabric_obj_val, void *data_val) {
    char *data_str_val = (char *) data_val;
    //if (data_str_val[4] != FE_DEF::FE_GET_LINK_DATA_COMMAND) {
    //    phwangDebugSSI(true, "Golbal::dFabricTpReceiveDataFunction", (char *) data_val, "index", phwangGetPortObjectIndex(port_obj_val));
    //}

    ((DFabricClass *) d_fabric_obj_val)->parseData(port_obj_val, (char *) data_val);
    phwangFree(data_val);
}

void DFabricClass::startNetServer (void)
{
    this->tcpServerObj_ = phwangMallocTpServer(this, TcpPortDefine::FABRIC_NODEJS_PORT_NUMER, dFabricTcoAcceptFunc, this, dFabricTpReceiveDataFunction, this, this->objectName());
}

void DFabricClass::setTimeStampString (void)
{
    time_t seconds = time(NULL);
    int time_stamp = (int) ((seconds - 1665633362) / 60);
    this->timeStampString_[0] = '{';
    phwangEncodeNumber(&this->timeStampString_[1], time_stamp, SIZE_DEF::FABRIC_TIME_STAMP_SIZE - 2);
    this->timeStampString_[SIZE_DEF::FABRIC_TIME_STAMP_SIZE - 1] = '}';
    this->timeStampString_[SIZE_DEF::FABRIC_TIME_STAMP_SIZE] = 0;

    phwangDebugS(true, "DFabricClass::setTimeStampString", this->timeStampString());
}
