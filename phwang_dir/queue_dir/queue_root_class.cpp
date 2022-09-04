/*
  Copyrights reserved
  Written by Paul Hwang
  File name: queue_root_class.cpp
*/

#include "../phwang.h"
#include "queue_root_class.h"

QueueRootClass::QueueRootClass (void)
{
    memset(this, 0, sizeof (*this));
}

QueueRootClass::~QueueRootClass(void)
{
}

void QueueRootClass::logit (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
}

void QueueRootClass::abend (char const* str0_val, char const* str1_val)
{
    phwangAbend(str0_val, str1_val);
}
