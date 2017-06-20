/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_export.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "u_theme_class.h"
#include "../theme_class.h"
#include "../d_theme_dir/d_theme_class.h"

void uThemeTpServerAcceptFunction (void *game_server_object_val, void *tp_transfer_object_val) {
    phwangLogit("Golbal::uThemeTpServerAcceptFunction", "");
    ((UThemeClass *) game_server_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void UThemeClass::exportedNetAcceptFunction (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
    sleep(1);
    baseMgrTest();
}

void uThemeTpReceiveDataFunction (void *game_server_object_val, void *data_val) {
    phwangLogit("Golbal::uThemeTpReceiveDataFunction", (char *) data_val);
    ((UThemeClass *) game_server_object_val)->exportedNetReceiveFunction((char *) data_val);
}

void UThemeClass::exportedNetReceiveFunction(char *data_val)
{
    this->logit("exportedNetReceiveFunction", data_val);
    this->theThemeObject->dThemeObject()->transmitFunction(data_val);
}

void UThemeClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, BASE_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, uThemeTpServerAcceptFunction, this, uThemeTpReceiveDataFunction, this, this->objectName());
}
