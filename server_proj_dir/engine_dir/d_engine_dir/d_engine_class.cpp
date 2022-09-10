/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/abend_dir/abend_class.h"
#include "../../protocol_dir/net_port_protocol.h"
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
    if (0) { /* debug */
        phwangLogit("Golbal::dEngineReceiveDataFromTransport", (char *) data_val);
    }

    ((DEngineClass *) game_d_server_object_val)->exportedParseFunction((char *) data_val);
    phwangFree(data_val);
}

void DEngineClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, THEME_ENGINE_PROTOCOL_TRANSPORT_PORT_NUMBER, dEngineReceiveDataFromTransport, this, this->objectName());
}
