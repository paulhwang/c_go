/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "d_theme_class.h"
#include "../theme_class.h"
#include "../u_theme_dir/u_theme_class.h"

void dThemeReceiveDataFromTransport (void *game_d_server_object_val, void *data_val) {
    phwangLogit("Golbal::dThemeReceiveDataFromTransport", (char *) data_val);
    ((DThemeClass *) game_d_server_object_val)->exportedNetReceiveFunction((char *) data_val);
}

void DThemeClass::exportedNetReceiveFunction(char *data_val)
{
    this->logit("exportedNetReceiveFunction", data_val);
    this->theThemeObject->uThemeObject()->transmitFunction(data_val);
}

void DThemeClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, GROUP_ROOM_PROTOCOL_TRANSPORT_PORT_NUMBER, dThemeReceiveDataFromTransport, this, this->objectName());
}
