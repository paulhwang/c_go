/*
  Copyrights reserved
  Written by Paul Hwang
  File name: tp_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "tp_class.h"

TpClass::TpClass (void *main_object_val)
{
    this->theMainObject = main_object_val;

    if (1) {
        this->logit("TpClass", "init");
    }
}

TpClass::~TpClass (void)
{
}

void TpClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void TpClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}

