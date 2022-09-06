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

void AbendClass::phwangDebug (int on_off_val, char const *func_name_val, char const *str1_val)
{
    if (this->theDebugCode && on_off_val) {
        this->phwangLogit(func_name_val, str1_val);
    }
};

void AbendClass::phwangDebug2 (int on_off_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (this->theDebugCode && on_off_val) {
        this->phwangLogit2(func_name_val, str1_val, str2_val);
    }
};

void AbendClass::phwangDebugInt (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (this->theDebugCode && on_off_val) {
        this->phwangLogitInt(func_name_val, str1_val, int1_val);
    }
}

void AbendClass::phwangDebugInt2 (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (this->theDebugCode && on_off_val) {
        this->phwangLogitInt2(func_name_val, str1_val, int1_val, str2_val, int2_val);
    }
}

void AbendClass::phwangLogit (char const *func_name_val, char const *str1_val)
{
    printf("%s() %s\n", func_name_val, str1_val);
}

void AbendClass::phwangLogit2 (char const *func_name_val, char const *str1_val, char const *str2_val)
{
    printf("%s() %s, %s\n", func_name_val, str1_val, str2_val);
}

void AbendClass::phwangLogitInt (char const *func_name_val, char const *str1_val, int int1_val)
{
    printf("%s() %s=%d\n", func_name_val, str1_val, int1_val);
}

void AbendClass::phwangLogitInt2 (char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    printf("%s() %s=%d, %s=%d\n", func_name_val, str1_val, int2_val, str2_val, int2_val);
}

void AbendClass::phwangAbend (char const *func_name_val, char const *str1_val)
{
    printf("*****ABEND******************************************\n");
    printf("%s() %s\n", func_name_val, str1_val);
    printf("*****ABEND******************************************\n");
    int *junk = 0;
    *junk = 0;
}

void AbendClass::phwangAbend2 (char const *func_name_val, char const *str1_val, char const *str2_val)
{
    printf("*****ABEND******************************************\n");
    printf("%s(), %s\n", func_name_val, str1_val, str2_val);
    printf("*****ABEND******************************************\n");
    int *junk = 0;
    *junk = 0;
}

void AbendClass::logit (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitBufSize];
    sprintf(s, "%s::%s", this->objectName(), func_name_val);
    this->phwangLogit(s, str1_val);
}

void AbendClass::abend (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitBufSize];
    sprintf(s, "%s::%s", this->objectName(), func_name_val);
    this->phwangAbend(s, str1_val);
}
