/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "u_theme_class.h"
#include "../theme_class.h"
#include "../d_theme_dir/d_theme_class.h"
#include "../room_class.h"

UThemeClass::UThemeClass (ThemeClass *theme_object_val)
{
    memset(this, 0, sizeof(UThemeClass));
    this->theThemeObject = theme_object_val;
    this->startNetServer();

    this->debug(true, "UThemeClass", "init");
}

UThemeClass::~UThemeClass (void)
{
}

void uThemeTpServerAcceptFunction (void *game_server_object_val, void *tp_transfer_object_val) {
    if (1) { /* debug */
        phwangLogit("Golbal::uThemeTpServerAcceptFunction", "");
    }

    ((UThemeClass *) game_server_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void UThemeClass::exportedNetAcceptFunction (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
}

void uThemeTpReceiveDataFunction (void *tp_transfer_object_val, void *game_server_object_val, void *data_val) {
    if (0) { /* debug */
        phwangLogit("Golbal::uThemeTpReceiveDataFunction", (char *) data_val);
    }

    ((UThemeClass *) game_server_object_val)->exportedParseFunction((char *) data_val);
    phwangFree(data_val, "uThemeTpReceiveDataFunction");
}

void UThemeClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, THEME_ENGINE_PROTOCOL_TRANSPORT_PORT_NUMBER, uThemeTpServerAcceptFunction, this, uThemeTpReceiveDataFunction, this, this->objectName());
}

void UThemeClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void UThemeClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
