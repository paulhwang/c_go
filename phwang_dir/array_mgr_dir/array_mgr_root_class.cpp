/*
  Copyrights reserved
  Written by Paul Hwang
  File name: array_mgr_root_class.cpp
*/

#include "../phwang.h"
#include "array_mgr_root_class.h"

ArrayMgrRootClass::ArrayMgrRootClass (void)
{
    memset(this, 0, sizeof (*this));
}

ArrayMgrRootClass::~ArrayMgrRootClass(void)
{
}

void ArrayMgrRootClass::logit (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
}

void ArrayMgrRootClass::abend (char const* str0_val, char const* str1_val)
{
    phwangAbend(str0_val, str1_val);
}
