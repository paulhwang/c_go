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
    this->theDebugCode = debug_code_val;
}

AbendClass::~AbendClass(void)
{
}

void AbendClass::phwangLogit (char const *str0_val, char const *str1_val)
{
    printf("%s() %s\n", str0_val, str1_val);
}

void AbendClass::phwangLogit3 (char const *str0_val, char const *str1_val, char const *str2_val)
{
    printf("%s() %s {%s}\n", str0_val, str1_val, str2_val);
}

void AbendClass::phwangAbend (char const *str0_val, char const *str1_val)
{
    printf("*****abend*****%s() %s\n", str0_val, str1_val);
    int *junk = 0;
    *junk = 0;
}

void AbendClass::phwangAbend3 (char const *str0_val, char const *str1_val, char const *str2_val)
{
    printf("*****abend*****%s() %s, %s\n", str0_val, str1_val, str2_val);
    int *junk = 0;
    *junk = 0;
}

void AbendClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->phwangLogit(s, str1_val);
}

void AbendClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->phwangAbend(s, str1_val);
}

void AbendClass::abend3 (char const *str0_val, char const *str1_val, char const *str2_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->phwangAbend3(s, str1_val, str2_val);
}
