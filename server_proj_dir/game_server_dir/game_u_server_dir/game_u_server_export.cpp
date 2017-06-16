/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_u_server_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "game_u_server_class.h"
#include "../../protocol_dir/net_port_protocol.h"

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
    ((GameUServerClass *) game_server_object_val)->exportedNetReceiveFunction(data_val);
}

void GameUServerClass::exportedNetReceiveFunction(void *data_val)
{
    phwangEnqueue(this->theReceiveQueue, data_val);
}

void GameUServerClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, gameUServerTpServerAcceptFunction, this, gameUServerTpReceiveDataFunction, this, this->objectName());
}
