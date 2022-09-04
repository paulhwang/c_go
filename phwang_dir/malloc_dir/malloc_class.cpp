/*
  Copyrights reserved
  Written by Paul Hwang
  File name: malloc_class.cpp
*/

#include "../phwang.h"
#include "malloc_class.h"

MallocClass::MallocClass (void)
{
    memset(this, 0, sizeof (*this));
    phwangIncrementObjectCount(&ObjectCount, ObjectName, 1);
}

MallocClass::~MallocClass(void)
{
    phwangDecrementObjectCount(&ObjectCount);
}

void MallocClass::logit (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
}

void MallocClass::abend (char const* str0_val, char const* str1_val)
{
    phwangAbend(str0_val, str1_val);
}
