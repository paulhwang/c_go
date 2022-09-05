/*
  Copyrights reserved
  Written by Paul Hwang
  File name: encode_class.cpp
*/

#include "../phwang.h"
#include "thread_root_class.h"

ThreadRootClass::ThreadRootClass (void)
{
    memset(this, 0, sizeof (*this));
}

ThreadRootClass::~ThreadRootClass(void)
{
}

void ThreadRootClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ThreadRootClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
