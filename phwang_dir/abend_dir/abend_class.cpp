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

void AbendClass::pDebug (int on_off_val, char const *func_name_val, char const *str1_val)
{
    if (this->theDebugCode && on_off_val) {
        this->pLogit(func_name_val, str1_val);
    }
};

void AbendClass::pDebug2 (int on_off_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (this->theDebugCode && on_off_val) {
        this->pLogit2(func_name_val, str1_val, str2_val);
    }
};

void AbendClass::pDebugInt (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (this->theDebugCode && on_off_val) {
        this->pLogitInt(func_name_val, str1_val, int1_val);
    }
}

void AbendClass::pDebugInt2 (int on_off_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (this->theDebugCode && on_off_val) {
        this->pLogitInt2(func_name_val, str1_val, int1_val, str2_val, int2_val);
    }
}

void AbendClass::pLogit (char const *func_name_val, char const *str1_val)
{
    printf("%s() %s\n", func_name_val, str1_val);
}

void AbendClass::pLogit2 (char const *func_name_val, char const *str1_val, char const *str2_val)
{
    printf("%s() %s, %s\n", func_name_val, str1_val, str2_val);
}

void AbendClass::pLogitInt (char const *func_name_val, char const *str1_val, int int1_val)
{
    printf("%s() %s=%d\n", func_name_val, str1_val, int1_val);
}

void AbendClass::pLogitInt2 (char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    printf("%s() %s=%d, %s=%d\n", func_name_val, str1_val, int1_val, str2_val, int2_val);
}

void AbendClass::pAbend (char const *func_name_val, char const *str1_val)
{
    printf("*****ABEND******************************************\n");
    printf("%s() %s\n", func_name_val, str1_val);
    printf("*****ABEND******************************************\n");
    int *junk = 0;
    *junk = 0;
}

void AbendClass::pAbend2 (char const *func_name_val, char const *str1_val, char const *str2_val)
{
    printf("*****ABEND******************************************\n");
    printf("%s(), %s\n", func_name_val, str1_val, str2_val);
    printf("*****ABEND******************************************\n");
    int *junk = 0;
    *junk = 0;
}

void AbendClass::composeFuncName(char *buf_val, char const *func_name_val)
{
    sprintf(buf_val, "%s::%s", this->objectName(), func_name_val);
}

void AbendClass::debug (int debug_on_val, char const *func_name_val, char const *str1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, func_name_val);
        phwangDebug(debug_on_val, s, str1_val);
    }
}

void AbendClass::debug2 (int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, func_name_val);
        phwangDebug2(debug_on_val, s, str1_val, str2_val);
    }
}

void AbendClass::debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, func_name_val);
        phwangDebugInt(debug_on_val, s, str1_val, int1_val);
    }
}

void AbendClass::debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        phwangComposeFuncName(s, func_name_val);
        phwangDebugInt2(debug_on_val, s, str1_val, int1_val, str2_val, int2_val);
    }
}

void AbendClass::logit (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, func_name_val);
    phwangLogit(s, str1_val);
}

void AbendClass::logit2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, func_name_val);
    phwangLogit2(s, str1_val, str2_val);
}

void AbendClass::logitInt(char const *func_name_val, char const *str1_val, int int1_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, func_name_val);
    phwangLogitInt(s, str1_val, int1_val);
}

void AbendClass::logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, func_name_val);
    phwangLogitInt2(s, str1_val, int1_val, str2_val, int2_val);
}

void AbendClass::abend (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, func_name_val);
    phwangAbend(s, str1_val);
}

void AbendClass::abend2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    phwangComposeFuncName(s, func_name_val);
    phwangAbend2(s, str1_val, str2_val);
}
