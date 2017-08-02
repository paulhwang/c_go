/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "d_engine_class.h"

DEngineClass::DEngineClass (EngineClass *engine_object_val)
{
    memset(this, 0, sizeof(DEngineClass));
    this->theEngineObject = engine_object_val;

    this->startNetConnect();

    this->debug(true, "DEngineClass", "init");
}

DEngineClass::~DEngineClass (void)
{
}

void dEngineReceiveDataFromTransport (void *tp_transfer_object_val, void *game_d_server_object_val, void *data_val) {
    phwangLogit("Golbal::dThemeReceiveDataFromTransport", (char *) data_val);
    ((DEngineClass *) game_d_server_object_val)->exportedparseFunction((char *) data_val);
    phwangFree(data_val);
}

void DEngineClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, dEngineReceiveDataFromTransport, this, this->objectName());
}

void DEngineClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DEngineClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
