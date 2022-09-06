/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_theme_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/abend_dir/abend_class.h"
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

    this->debug(false, "UThemeClass", "init");
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
        this->abend("exportedNetAcceptFunction", "null tp_transfer_object_val");
        return;
    }

    this->theTpTransferObject = tp_transfer_object_val;
}

void uThemeTpReceiveDataFunction (void *tp_transfer_object_val, void *game_server_object_val, void *data_val) {
    if (0) { /* debug */
        phwangLogit("Golbal::uThemeTpReceiveDataFunction", (char *) data_val);
    }

    ((UThemeClass *) game_server_object_val)->exportedParseFunction((char *) data_val);
    phwangFree(data_val);
}

void UThemeClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, THEME_ENGINE_PROTOCOL_TRANSPORT_PORT_NUMBER, uThemeTpServerAcceptFunction, this, uThemeTpReceiveDataFunction, this, this->objectName());
}

void UThemeClass::debug (int debug_on_val, char const *func_name_val, char const *str1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebug(debug_on_val, s, str1_val);
    }
}

void UThemeClass::debug2 (int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebug2(debug_on_val, s, str1_val, str2_val);
    }
}

void UThemeClass::debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebugInt(debug_on_val, s, str1_val, int1_val);
    }
}

void UThemeClass::debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebugInt2(debug_on_val, s, str1_val, int1_val, str2_val, int2_val);
    }
}

void UThemeClass::logit (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogit(s, str1_val);
}

void UThemeClass::logit2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogit2(s, str1_val, str2_val);
}

void UThemeClass::logitInt(char const *func_name_val, char const *str1_val, int int1_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogitInt(s, str1_val, int1_val);
}

void UThemeClass::logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogitInt2(s, str1_val, int1_val, str2_val, int2_val);
}

void UThemeClass::abend (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangAbend(s, str1_val);
}

void UThemeClass::abend2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangAbend2(s, str1_val, str2_val);
}
