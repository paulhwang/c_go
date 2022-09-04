/*
  Copyrights reserved
  Written by Paul Hwang
  File name: encode_class.cpp
*/

#include "../phwang.h"
#include "encode_class.h"

EncodeClass::EncodeClass (void)
{
    memset(this, 0, sizeof (*this));
    phwangIncrementObjectCount(&ObjectCount, ObjectName, 1);
}

EncodeClass::~EncodeClass(void)
{
    phwangDecrementObjectCount(&ObjectCount);
}

void EncodeClass::logit (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
}

void EncodeClass::abend (char const* str0_val, char const* str1_val)
{
    phwangAbend(str0_val, str1_val);
}
