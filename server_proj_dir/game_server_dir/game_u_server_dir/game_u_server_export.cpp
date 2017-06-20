/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_u_server_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "game_u_server_class.h"
#include "../theme_class.h"
#include "../game_d_server_dir/d_theme_class.h"

void gameUServerTpServerAcceptFunction (void *game_server_object_val, void *tp_transfer_object_val) {
    phwangLogit("Golbal::gameUServerTpServerAcceptFunction", "");
    ((GameUServerClass *) game_server_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void GameUServerClass::exportedNetAcceptFunction (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
    sleep(1);
    baseMgrTest();
}

void gameUServerTpReceiveDataFunction (void *game_server_object_val, void *data_val) {
    phwangLogit("Golbal::gameUServerTpReceiveDataFunction", (char *) data_val);
    ((GameUServerClass *) game_server_object_val)->exportedNetReceiveFunction((char *) data_val);
}

void GameUServerClass::exportedNetReceiveFunction(char *data_val)
{
    this->logit("exportedNetReceiveFunction", data_val);
    this->theGameServerObject->gameDServerObject()->transmitFunction(data_val);
}

void GameUServerClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, gameUServerTpServerAcceptFunction, this, gameUServerTpReceiveDataFunction, this, this->objectName());
}
