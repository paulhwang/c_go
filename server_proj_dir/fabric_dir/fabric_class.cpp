/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "fabric_class.h"
#include "u_fabric_dir/u_fabric_class.h"
#include "d_fabric_dir/d_fabric_class.h"

FabricClass::FabricClass (void *main_object_val)
{
    memset(this, 0, sizeof(FabricClass));
    this->theMainObject = main_object_val;
    this->theUFabricObject = new UFabricClass(this);
    this->theDFabricObject = new DFabricClass(this);

    if (1) {
        this->logit("FabricClass", "init");
    }
}

FabricClass::~FabricClass (void)
{
}

void FabricClass::startThreads (void)
{
    this->theDFabricObject->startThreads();
    this->theUFabricObject->startThreads();
}

void FabricClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void FabricClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}