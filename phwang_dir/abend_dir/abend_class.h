/*
  Copyrights reserved
  Written by Paul Hwang
  File name: abend_class.h
*/

#pragma once

class AbendClass
{
public:
    int const static LogitFuncNameBufSize = 512;

    AbendClass(int debug_code_val);
    ~AbendClass(void);

    void pDebug(int on_off_val, char const *func_name_val, char const *str1_val);
    void pDebug2(int on_off_val, char const *func_name_val, char const *str1_val, char const *str2_val);

    void pDebugInt(int on_off_val, char const *func_name_val, char const *str1_val, int int1_val);
    void pDebugInt2(int on_off_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);

    void pLogit(char const *func_name_val, char const *str1_val);
    void pLogit2(char const *func_name_val, char const *str1_val, char const *str2_val);

    void pLogitInt(char const *func_name_val, char const *str1_val, int int1_val);
    void pLogitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);

    void pAbend(char const *func_name_val, char const *str1_val);
    void pAbend2(char const *func_name_val, char const *str1_val, char const *str2_val);

private:
    char const *objectName(void) {return "AbendClass";}
    int theDebugCode;

    void composeFuncName(char *buf_val, char *func_name_val);
    void debug(int debug_on_val, char const *func_name_val, char const *str1_val);
    void debug2(int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val);
    void debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val);
    void debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void logit(char const *func_name_val, char const *str1_val);
    void logit2(char const *func_name_val, char const *str1_val, char const *str2_val);
    void logitInt(char const *func_name_val, char const *str1_val, int int1_val);
    void logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void abend(char const *func_name_val, char const *str1_val);
    void abend2(char const *func_name_val, char const *str1_val, char const *str2_val);
};
