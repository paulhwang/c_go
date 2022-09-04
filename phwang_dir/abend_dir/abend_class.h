/*
  Copyrights reserved
  Written by Paul Hwang
  File name: abemd_class.h
*/

#pragma once

class AbendClass
{
    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    AbendClass(void);
    ~AbendClass(void);
    char const *objectName(void) {return "AbendClass";}
};
