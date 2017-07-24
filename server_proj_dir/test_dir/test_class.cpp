/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "test_class.h"

TestClass::TestClass(void)
{
}

TestClass::~TestClass(void)
{
}

void TestClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void TestClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
