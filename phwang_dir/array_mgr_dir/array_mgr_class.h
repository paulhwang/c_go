/*
  Copyrights reserved
  Written by Paul Hwang
  File name: array_mgr_class.h
*/

#pragma once

class ArrayMgrClass {
    char *theCallerName;
    char theArrayType;
    int theArraySize;

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class PhwangClass;

public:
    ArrayMgrClass(char *caller_name_val, char array_type_val, int array_size_val);
    ~ArrayMgrClass(void);
    char const* objectName(void) {return "ArrayMgrClass";}
};
