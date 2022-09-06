/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_transfer_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/abend_dir/abend_class.h"
#include "tp_transfer_class.h"

TpTransferClass::TpTransferClass (int socket_val,
                                  void (*receive_callback_val)(void *, void *, void *),
                                  void *receive_object_val,
                                  char const *who_val)
{
    memset(this, 0, sizeof(*this));
    this->theSocket = socket_val;
    this->theReceiveCallback = receive_callback_val;
    this->theReceiveObject = receive_object_val;
    this->theWho = who_val;
    this->setMaxDataSize();

    this->theReceiveQueue = phwangMallocSuspendedQueue(TpTransferClass::RECEIVE_QUEUE_SIZE);
    this->theTransmitQueue = phwangMallocSuspendedQueue(TpTransferClass::TRANSMIT_QUEUE_SIZE);

    if (1) { /* debug */
        char s[128];
        sprintf(s, "init for (%s) %d", this->theWho, this->maxDataSize());
        this->logit("TpTransferClass", s);
    }
}

TpTransferClass::~TpTransferClass (void)
{
}

void TpTransferClass::startThreads (int index_val)
{
    if (1) { /* debug */
        char s[128];
        sprintf(s, "threads started for (%s) index=%i", this->theWho, index_val);
        this->logit("startThreads", s);
    }

    this->theIndex = index_val;
    this->startReceiveThread2();
    this->startReceiveThread(this->theSocket);
    this->startTransmitThread(this->theSocket);
}

void TpTransferClass::debug (int debug_on_val, char const *func_name_val, char const *str1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebug(debug_on_val, s, str1_val);
    }
}

void TpTransferClass::debug2 (int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebug2(debug_on_val, s, str1_val, str2_val);
    }
}

void TpTransferClass::debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebugInt(debug_on_val, s, str1_val, int1_val);
    }
}

void TpTransferClass::debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, this->objectName(), func_name_val);
        phwangDebugInt2(debug_on_val, s, str1_val, int1_val, str2_val, int2_val);
    }
}

void TpTransferClass::logit (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogit(s, str1_val);
}

void TpTransferClass::logit2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogit2(s, str1_val, str2_val);
}

void TpTransferClass::logitInt(char const *func_name_val, char const *str1_val, int int1_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogitInt(s, str1_val, int1_val);
}

void TpTransferClass::logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangLogitInt2(s, str1_val, int1_val, str2_val, int2_val);
}

void TpTransferClass::abend (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangAbend(s, str1_val);
}

void TpTransferClass::abend2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, this->objectName(), func_name_val);
    phwangAbend2(s, str1_val, str2_val);
}
