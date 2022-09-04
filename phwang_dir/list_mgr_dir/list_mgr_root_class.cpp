/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_root_class.cpp
*/

#include "../phwang.h"
#include "list_mgr_root_class.h"

ListMgrRootClass::ListMgrRootClass (void)
{
    memset(this, 0, sizeof (*this));
}

ListMgrRootClass::~ListMgrRootClass(void)
{
}

void ListMgrRootClass::logit (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
}

void ListMgrRootClass::abend (char const* str0_val, char const* str1_val)
{
    phwangAbend(str0_val, str1_val);
}
