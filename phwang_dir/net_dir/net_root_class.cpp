/*
  Copyrights reserved
  Written by Paul Hwang
  File name: net_root_class.cpp
*/

#include "../phwang.h"
#include "net_root_class.h"

NetRootClass::NetRootClass (void)
{
    memset(this, 0, sizeof (*this));
}

NetRootClass::~NetRootClass(void)
{
}

void NetRootClass::logit (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
}

void NetRootClass::abend (char const* str0_val, char const* str1_val)
{
    phwangAbend(str0_val, str1_val);
}
