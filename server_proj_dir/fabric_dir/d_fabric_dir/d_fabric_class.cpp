/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_fabric_class.h"

DFabricClass::DFabricClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(DFabricClass));
    this->theFabricObject = fabric_object_val;
    this->theReceiveQueue = phwangMallocQueue(D_FABRIC_RECEIVE_QUEUE_SIZE);

    if (1) {
        this->logit("DFabricClass", "init");
    }
}

DFabricClass::~DFabricClass (void)
{
}

void DFabricClass::startThreads (void)
{
    //this->startReceiveThread();
}

void DFabricClass::debug (int on_off_val, char const* str0_val, char const* str1_val)
{
    if (on_off_val) {
        this->logit(str0_val, str1_val);
    }
}

void DFabricClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DFabricClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
