/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../define_dir/tcp_port_define.h"
#include "d_theme_class.h"

DThemeClass::DThemeClass (int debug_on_val, ThemeClass *theme_object_val)
{
    memset(this, 0, sizeof(DThemeClass));
    this->debugOn_ = true && debug_on_val;
    this->themeObj_ = theme_object_val;

    this->startNetConnect();

    phwangDebugS(false, "DThemeClass::DThemeClass", "init");
}

DThemeClass::~DThemeClass (void)
{
}

void dThemeReceiveDataFromTransport (void *port_object_val, void *game_d_server_object_val, void *data_val) {
    if (false) {
        printf("Golbal::dThemeReceiveDataFromTransport() %s\n", (char *) data_val);
    }

    ((DThemeClass *) game_d_server_object_val)->parseData((char *) data_val);
    phwangFree(data_val);
}

void DThemeClass::startNetConnect (void)
{
    this->thePortObject = phwangTpConnect(this->debugOn_, 0, TcpPortDefine::FABRIC_THEME_PORT_NUMER, dThemeReceiveDataFromTransport, this, this->objectName());
}
