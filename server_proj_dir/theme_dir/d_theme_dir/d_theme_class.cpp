/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/abend_dir/abend_class.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "d_theme_class.h"

DThemeClass::DThemeClass (ThemeClass *theme_object_val)
{
    memset(this, 0, sizeof(DThemeClass));
    this->theThemeObject = theme_object_val;

    this->startNetConnect();

    this->debug(false, "DThemeClass", "init");
}

DThemeClass::~DThemeClass (void)
{
}

void dThemeReceiveDataFromTransport (void *tp_transfer_object_val, void *game_d_server_object_val, void *data_val) {
    if (0) { /* debug */
        phwangLogit("Golbal::dThemeReceiveDataFromTransport", (char *) data_val);
    }

    ((DThemeClass *) game_d_server_object_val)->exportedParseFunction((char *) data_val);
    phwangFree(data_val);
}

void DThemeClass::startNetConnect (void)
{
    printf("DThemeClass::startNetConnect() aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
    this->theTpTransferObject = phwangTpConnect(0, FABRIC_THEME_PROTOCOL_TRANSPORT_PORT_NUMBER, dThemeReceiveDataFromTransport, this, this->objectName());
}

void DThemeClass::debug (int debug_on_val, char const *func_name_val, char const *str1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebug(debug_on_val, s, str1_val);
    }
}

void DThemeClass::debug2 (int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebug2(debug_on_val, s, str1_val, str2_val);
    }
}

void DThemeClass::debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebugInt(debug_on_val, s, str1_val, int1_val);
    }
}

void DThemeClass::debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebugInt2(debug_on_val, s, str1_val, int1_val, str2_val, int2_val);
    }
}

void DThemeClass::logit (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogit(s, str1_val);
}

void DThemeClass::logit2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogit2(s, str1_val, str2_val);
}

void DThemeClass::logitInt(char const *func_name_val, char const *str1_val, int int1_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogitInt(s, str1_val, int1_val);
}

void DThemeClass::logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogitInt2(s, str1_val, int1_val, str2_val, int2_val);
}

void DThemeClass::abend (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangAbend(s, str1_val);
}

void DThemeClass::abend2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangAbend2(s, str1_val, str2_val);
}
