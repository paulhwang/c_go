/*
  Copyrights reserved
  Written by Paul Hwang
  File name: encode_class.h
*/

#pragma once

class EncodeClass
{
    inline static char *ObjectName = "EncodeClass";
    inline static int ObjectCount = 0;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    EncodeClass(void);
    ~EncodeClass(void);
};
