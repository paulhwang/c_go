/*
  Copyrights reserved
  Written by Paul Hwang
  File name: array_mgr_class.h
*/

#pragma once

class ArrayMgrClass {
    char const *theWho;
    char theArrayType;
    int theMaxArraySize;
    int theArraySize;
    void **thePointerArrayTable;

    void allocArrayTable(void);
    void insertPointerElement(void *element_val);
    void removePointerElement(void *element_val);

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
    void composeFuncNameExtra(char *buf_val, char const *func_name_val) {phwangComposeFuncNameExtra(buf_val, this->objectName(), func_name_val, this->theWho);}

public:
    ArrayMgrClass(char const *who_val, char array_type_val, int max_array_size_val);
    ~ArrayMgrClass(void);
    char const* objectName(void) {return "ArrayMgrClass";}

    void *getArrayTable(int *array_size_ptr);
    void insertElement(void *element_val);
    void removeElement(void *element_val);
};
