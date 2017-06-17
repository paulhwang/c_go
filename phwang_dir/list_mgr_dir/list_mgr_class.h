/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.h
*/

#pragma once

class ListMgrClass {

    void debug(int on_off_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    ListMgrClass(void);
    ~ListMgrClass(void);
    char const* objectName(void) {return "ListMgrClass";}
};
