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

private:
    char const *objectName(void) {return "AbendClass";}
};
