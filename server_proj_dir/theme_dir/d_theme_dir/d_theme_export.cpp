/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_dserver_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "d_theme_class.h"
#include "../theme_class.h"
#include "../u_theme_dir/u_theme_class.h"

void gameDServerReceiveDataFromTransport (void *game_d_server_object_val, void *data_val) {
    phwangLogit("Golbal::gameDServerReceiveDataFromTransport", (char *) data_val);
    ((GameDServerClass *) game_d_server_object_val)->exportedNetReceiveFunction((char *) data_val);
}

void GameDServerClass::exportedNetReceiveFunction(char *data_val)
{
    this->logit("exportedNetReceiveFunction", data_val);
    this->theGameServerObject->gameUServerObject()->transmitFunction(data_val);
}

void GameDServerClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, GROUP_ROOM_PROTOCOL_TRANSPORT_PORT_NUMBER, gameDServerReceiveDataFromTransport, this, this->objectName());
}
