/*
  Copyrights reserved
  Written by Paul Hwang
  File name: abend_class.h
*/

#pragma once

class AbendClass
{
    char const *objectName(void) {return "AbendClass";}
    int theDebugCode;

    void debug(int on_off_val, char const *func_name_val, char const *str1_val) {if (on_off_val) this->logit(func_name_val, str1_val);};
    void logit(char const *func_name_val, char const *str1_val);
    void abend(char const *func_name_val, char const *str1_val);

public:
    AbendClass(int debug_code_val);
    ~AbendClass(void);
    int const static LogitBufSize = 512;

    void phwangDebug(int on_off_val, char const *func_name_val, char const *str1_val);
    void phwangDebug2(int on_off_val, char const *func_name_val, char const *str1_val, char const *str2_val);

    void phwangDebugInt(int on_off_val, char const *func_name_val, char const *str1_val, int int1_val);
    void phwangDebugInt2(int on_off_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);

    void phwangLogit(char const *func_name_val, char const *str1_val);
    void phwangLogit2(char const *func_name_val, char const *str1_val, char const *str2_val);

    void phwangLogitInt(char const *func_name_val, char const *str1_val, int int1_val);
    void phwangLogitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);

    void phwangAbend(char const *func_name_val, char const *str1_val);
    void phwangAbend2(char const *func_name_val, char const *str1_val, char const *str2_val);
};
