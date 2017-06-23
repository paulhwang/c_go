/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_engine_class.h"

DEngineClass::DEngineClass (void)
{
    memset(this, 0, sizeof(DEngineClass));

    this->debug(true, "DEngineClass", "init");
}

DEngineClass::~DEngineClass (void)
{
}

void DEngineClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DEngineClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
