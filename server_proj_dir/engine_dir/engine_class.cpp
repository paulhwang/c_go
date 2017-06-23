/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "engine_class.h"
#include "base_mgr_dir/base_mgr_class.h"
#include "d_engine_dir/d_engine_class.h"

EngineClass::EngineClass (void)
{
    memset(this, 0, sizeof(EngineClass));
    this->theDEngineObject = new DEngineClass();
    this->theGoBaseMgrObject = new BaseMgrClass();

    this->debug(true, "EngineClass", "init");
}

EngineClass::~EngineClass (void)
{
    this->theGoBaseMgrObject->~BaseMgrClass(); 
    this->theDEngineObject->~DEngineClass();
}

void EngineClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void EngineClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
