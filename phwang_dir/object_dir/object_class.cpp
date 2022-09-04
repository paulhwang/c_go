/*
  Copyrights reserved
  Written by Paul Hwang
  File name: object_class.cpp
*/

#include "../phwang.h"
#include "object_class.h"

ObjectClass::ObjectClass (void)
{
    memset(this, 0, sizeof (*this));
    phwangIncrementObjectCount(&ObjectCount, ObjectName, 1);
}

ObjectClass::~ObjectClass(void)
{
    phwangDecrementObjectCount(&ObjectCount);
}

void ObjectClass::logit (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
}

void ObjectClass::abend (char const* str0_val, char const* str1_val)
{
    phwangAbend(str0_val, str1_val);
}
