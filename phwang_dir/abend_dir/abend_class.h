/*
  Copyrights reserved
  Written by Paul Hwang
  File name: abend_class.h
*/

#pragma once

class AbendClass
{
    inline static char *ObjectName = "AbendClass";

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void logit3(char const *str0_val, char const *str1_val, char const *str2_val);
    void abend(char const *str0_val, char const *str1_val);
    void abend3(char const *str0_val, char const *str1_val, char const *str2_val);

public:
    AbendClass(void);
    ~AbendClass(void);

    void phwangDebug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->phwangLogit(str0_val, str1_val);}
    void phwangLogit(char const *str0_val, char const *str1_val);
    void phwangLogit3(char const *str0_val, char const *str1_val, char const *str2_val);
    void phwangAbend(char const *str0_val, char const *str1_val);
    void phwangAbend3(char const *str0_val, char const *str1_val, char const *str2_val);
};
