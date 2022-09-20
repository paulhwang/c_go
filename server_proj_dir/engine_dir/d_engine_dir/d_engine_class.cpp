/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../define_dir/tcp_port_define.h"
#include "d_engine_class.h"

DEngineClass::DEngineClass (EngineClass *engine_object_val)
{
    memset(this, 0, sizeof(DEngineClass));
    this->theEngineObject = engine_object_val;

    this->startNetConnect();

    phwangDebugS(false, "DEngineClass::DEngineClass", "init");
}

DEngineClass::~DEngineClass (void)
{
}

void dEngineReceiveDataFromTransport (void *tp_transfer_object_val, void *game_d_server_object_val, void *data_val) {
    phwangDebugS(false, "Golbal::dEngineReceiveDataFromTransport", (char *) data_val);

    ((DEngineClass *) game_d_server_object_val)->exportedParseFunction((char *) data_val);
    phwangFree(data_val);
}

void DEngineClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, TcpPortDefine::THEME_ENGINE_PORT_NUMER, dEngineReceiveDataFromTransport, this, this->objectName());
}
