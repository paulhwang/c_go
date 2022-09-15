/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/abend_dir/abend_class.h"
#include "../../define_dir/tcp_port_define.h"
#include "../../define_dir/te_def.h"
#include "u_theme_class.h"
#include "../theme_class.h"
#include "../d_theme_dir/d_theme_class.h"
#include "../room_class.h"

UThemeClass::UThemeClass (ThemeClass *theme_object_val)
{
    memset(this, 0, sizeof(UThemeClass));
    this->theThemeObject = theme_object_val;
    this->startNetServer();

    phwangDebugS(false, "UThemeClass::UThemeClass", "init");
}

UThemeClass::~UThemeClass (void)
{
}

void uThemeTpServerAcceptFunction (void *game_server_object_val, void *tp_transfer_object_val) {
    ((UThemeClass *) game_server_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void UThemeClass::exportedNetAcceptFunction (void *tp_transfer_object_val)
{
    if (!tp_transfer_object_val) {
        phwangAbendS("UThemeClass::exportedNetAcceptFunction", "null tp_transfer_object_val");
        return;
    }

    this->theTpTransferObject = tp_transfer_object_val;
}

void uThemeTpReceiveDataFunction (void *tp_transfer_object_val, void *game_server_object_val, void *data_val) {
    if (0) { /* debug */
        phwangLogitS("Golbal::uThemeTpReceiveDataFunction", (char *) data_val);
    }

    ((UThemeClass *) game_server_object_val)->exportedParseFunction((char *) data_val);
    phwangFree(data_val);
}

void UThemeClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, TcpPortDefine::THEME_ENGINE_PORT_NUMER, uThemeTpServerAcceptFunction, this, uThemeTpReceiveDataFunction, this, this->objectName());
}
