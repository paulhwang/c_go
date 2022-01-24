/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "d_theme_class.h"

DThemeClass::DThemeClass (ThemeClass *theme_object_val)
{
    memset(this, 0, sizeof(DThemeClass));
    this->theThemeObject = theme_object_val;

    this->startNetConnect();

    if (1) { /* debug */
        this->logit("DThemeClass", "init");
    }
}

DThemeClass::~DThemeClass (void)
{
}

void dThemeReceiveDataFromTransport (void *tp_transfer_object_val, void *game_d_server_object_val, void *data_val) {
    if (0) { /* debug */
        phwangLogit("Golbal::dThemeReceiveDataFromTransport", (char *) data_val);
    }

    ((DThemeClass *) game_d_server_object_val)->exportedParseFunction((char *) data_val);
    phwangFree(data_val, "dThemeReceiveDataFromTransport");
}

void DThemeClass::startNetConnect (void)
{
    printf("DThemeClass::startNetConnect() aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
    this->theTpTransferObject = phwangTpConnect(0, FABRIC_THEME_PROTOCOL_TRANSPORT_PORT_NUMBER, dThemeReceiveDataFromTransport, this, this->objectName());
}

void DThemeClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DThemeClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
