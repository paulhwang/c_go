/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_dserver_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "game_d_server_class.h"
#include "../../protocol_dir/game_server_protocol.h"

void gameDServerReceiveDataFromTransport (void *game_d_server_object_val, void *data_val) {
    phwangLogit("Golbal::gameDServerReceiveDataFromTransport", (char *) data_val);
    ((GameDServerClass *) game_d_server_object_val)->exportedNetReceiveFunction(data_val);
}

void GameDServerClass::exportedNetReceiveFunction(void *data_val)
{
    this->logit("exportedNetReceiveFunction", (char *) data_val);
    phwangEnqueue(this->theReceiveQueue, data_val);
}

void GameDServerClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, GROUP_ROOM_PROTOCOL_TRANSPORT_PORT_NUMBER, gameDServerReceiveDataFromTransport, this, this->objectName());
}
