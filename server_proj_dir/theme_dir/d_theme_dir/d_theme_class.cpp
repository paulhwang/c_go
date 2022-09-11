/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/abend_dir/abend_class.h"
#include "../../protocol_dir/tcp_port_class.h"
#include "d_theme_class.h"

DThemeClass::DThemeClass (ThemeClass *theme_object_val)
{
    memset(this, 0, sizeof(DThemeClass));
    this->theThemeObject = theme_object_val;

    this->startNetConnect();

    phwangDebugS(false, "DThemeClass::DThemeClass", "init");
}

DThemeClass::~DThemeClass (void)
{
}

void dThemeReceiveDataFromTransport (void *tp_transfer_object_val, void *game_d_server_object_val, void *data_val) {
    if (0) { /* debug */
        phwangLogitS("Golbal::dThemeReceiveDataFromTransport", (char *) data_val);
    }

    ((DThemeClass *) game_d_server_object_val)->exportedParseFunction((char *) data_val);
    phwangFree(data_val);
}

void DThemeClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, TcpPortClass::FABRIC_THEME_PORT_NUMER, dThemeReceiveDataFromTransport, this, this->objectName());
}
