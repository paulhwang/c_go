/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_fabric_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/abend_dir/abend_class.h"
#include "../../protocol_dir/net_port_protocol.h"
#include "u_fabric_class.h"

UFabricClass::UFabricClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(UFabricClass));
    this->theFabricObject = fabric_object_val;
    this->startNetServer();

    if (1) { /* debug */
        this->logit("UFabricClass", "init");
    }
}

UFabricClass::~UFabricClass (void)
{
}

void uFabricTpServerAcceptFunction (void *u_fabric_object_val, void *tp_transfer_object_val) {
    phwangDebug(true, "*****Golbal::uFabricTpServerAcceptFunction", "accepted (http client)");
    if (!tp_transfer_object_val) {
        phwangAbend("Golbal::uFabricTpServerAcceptFunction", "null tp_transfer_object_val");
    }

    ((UFabricClass *) u_fabric_object_val)->exportedNetAcceptFunction(tp_transfer_object_val);
}

void UFabricClass::exportedNetAcceptFunction (void *tp_transfer_object_val)
{
    this->theTpTransferObject = tp_transfer_object_val;
}

void uFabricTpReceiveDataFunction (void *tp_transfer_object_val, void *u_fabric_object_val, void *data_val) {
    if (0) { /* debug */
        phwangLogit("Golbal::uFabricTpReceiveDataFunction", (char *) data_val);
    }

    ((UFabricClass *) u_fabric_object_val)->exportedParseFunction((char *) data_val);
    phwangFree(data_val);
}

void UFabricClass::startNetServer (void)
{
    this->theTpServerObject = phwangMallocTpServer(this, FABRIC_THEME_PROTOCOL_TRANSPORT_PORT_NUMBER, uFabricTpServerAcceptFunction, this, uFabricTpReceiveDataFunction, this, this->objectName());
}

void UFabricClass::debug (int debug_on_val, char const *func_name_val, char const *str1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebug(debug_on_val, s, str1_val);
    }
}

void UFabricClass::debug2 (int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebug2(debug_on_val, s, str1_val, str2_val);
    }
}

void UFabricClass::debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebugInt(debug_on_val, s, str1_val, int1_val);
    }
}

void UFabricClass::debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebugInt2(debug_on_val, s, str1_val, int1_val, str2_val, int2_val);
    }
}

void UFabricClass::logit (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogit(s, str1_val);
}

void UFabricClass::logit2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogit2(s, str1_val, str2_val);
}

void UFabricClass::logitInt(char const *func_name_val, char const *str1_val, int int1_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogitInt(s, str1_val, int1_val);
}

void UFabricClass::logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogitInt2(s, str1_val, int1_val, str2_val, int2_val);
}

void UFabricClass::abend (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangAbend(s, str1_val);
}

void UFabricClass::abend2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangAbend2(s, str1_val, str2_val);
}
