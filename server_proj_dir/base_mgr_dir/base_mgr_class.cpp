/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "base_mgr_class.h"
#include "go_base_dir/go_base_class.h"

BaseMgrClass::BaseMgrClass (void)
{
    memset(this, 0, sizeof(BaseMgrClass));
    this->theGlobalBaseId = 0;
    this->theReceiveQueue = phwangMallocQueue(BASE_MGR_RECEIVE_QUEUE_SIZE);

    if (1) {
        this->logit("BaseMgrClass", "init");
    }
}

BaseMgrClass::~BaseMgrClass (void)
{
    phwangFreeTpTransfer(this->theTpTransferObject); 
    phwangFreeQueue(this->theReceiveQueue);
}

void BaseMgrClass::startThreads (void)
{
    this->startReceiveThread();
}

void BaseMgrClass::baseMgrLogit (char const* str0_val, char const* str1_val) {
    phwangLogit(str0_val, str1_val);
}

void BaseMgrClass::baseMgrAbend (char const* str0_val, char const* str1_val) {
    phwangAbend(str0_val, str1_val);
}

void BaseMgrClass::debug (int on_off_val, char const* str0_val, char const* str1_val)
{
    if (on_off_val) {
        this->logit(str0_val, str1_val);
    }
}

void BaseMgrClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseMgrLogit(s, str1_val);
}

void BaseMgrClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseMgrAbend(s, str1_val);
}

