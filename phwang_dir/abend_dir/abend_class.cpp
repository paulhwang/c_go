/*
  Copyrights reserved
  Written by Paul Hwang
  File name: abend_class.cpp
*/

#include "../phwang.h"
#include "abend_class.h"

AbendClass::AbendClass (int debug_code_val)
{
    memset(this, 0, sizeof (*this));
}

AbendClass::~AbendClass(void)
{
}
