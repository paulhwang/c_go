/*
  Copyrights reserved
  Written by Paul Hwang
  File name: abemd_class.cpp
*/

#include "../phwang.h"
#include "abend_class.h"

AbendClass::AbendClass (void)
{
    memset(this, 0, sizeof (*this));
}

AbendClass::~AbendClass(void)
{
}

void AbendClass::logit (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
}

void AbendClass::abend (char const* str0_val, char const* str1_val)
{
    phwangAbend(str0_val, str1_val);
}
