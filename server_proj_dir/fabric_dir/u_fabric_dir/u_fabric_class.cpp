/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_fabric_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../define_dir/tcp_port_define.h"
#include "u_fabric_class.h"

UFabricClass::UFabricClass (int debug_on_val, FabricClass *fabric_obj_val)
{
    memset(this, 0, sizeof(UFabricClass));
    this->debugOn_ = true && debug_on_val;
    this->fabricObj_ = fabric_obj_val;
    this->startNetServer();

    phwangDebugS(false, "UFabricClass::UFabricClass", "init");
}

UFabricClass::~UFabricClass (void)
{
}

void uFabricTpServerAcceptFunction (void *u_fabric_object_val, void *tp_transfer_object_val) {
    ((UFabricClass *) u_fabric_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void UFabricClass::exportedNetAcceptFunction (void *port_object_val)
{
    if (!port_object_val) {
        phwangAbendS("UFabricClass::exportedNetAcceptFunction", "null port_object_val");
        return;
    }
    this->portObject_ = port_object_val;
}

void uFabricTpReceiveDataFunction (void *port_object_val, void *u_fabric_object_val, void *data_val) {
    if (0) { /* debug */
        phwangLogitS("Golbal::uFabricTpReceiveDataFunction", (char *) data_val);
    }

    ((UFabricClass *) u_fabric_object_val)->parseData((char *) data_val);
    phwangFree(data_val);
}

void UFabricClass::startNetServer (void)
{
    this->tcpServerObject_ = phwangMallocTpServer(this->debugOn_, this, TcpPortDefine::FABRIC_THEME_PORT_NUMER, uFabricTpServerAcceptFunction, this, uFabricTpReceiveDataFunction, this, this->objectName());
}
