/*
  Copyrights reserved
  Written by Paul Hwang
  File name: encode_class.cpp
*/

#include "../phwang.h"
#include "thread_root_class.h"

ThreadRootClass::ThreadRootClass (int debug_code_val)
{
    memset(this, 0, sizeof (*this));
}

ThreadRootClass::~ThreadRootClass(void)
{
}

int ThreadRootClass::pthreadCreate(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
{
    return pthread_create(thread, attr, start_routine, arg);
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
