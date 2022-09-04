/*
  Copyrights reserved
  Written by Paul Hwang
  File name: net_root_class.h
*/

#pragma once

class NetRootClass
{
    inline static char *ObjectName = "NetRootClass";

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    NetRootClass(void);
    ~NetRootClass(void);
};
