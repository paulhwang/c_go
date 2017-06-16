/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_fabric_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_fabric_class.h"
#include "group_mgr_dir/group_mgr_class.h"

UFabricClass::UFabricClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(UFabricClass));
    this->theFabricObject = fabric_object_val;
    this->theReceiveQueue = phwangMallocQueue(U_FABRIC_RECEIVE_QUEUE_SIZE);
    this->startNetServer();

    if (1) {
        this->logit("UFabricClass", "init");
    }
}

UFabricClass::~UFabricClass (void)
{
}

void UFabricClass::startThreads (void)
{
    this->startReceiveThread();
}

void UFabricClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void UFabricClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
