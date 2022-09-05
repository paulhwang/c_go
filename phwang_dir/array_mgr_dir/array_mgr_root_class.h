/*
  Copyrights reserved
  Written by Paul Hwang
  File name: array_mgr_root_class.h
*/

#pragma once

class ArrayMgrRootClass
{
    char const *objectName(void) {return "ArrayMgrRootClass";}

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    ArrayMgrRootClass(void);
    ~ArrayMgrRootClass(void);
    
    void *arrayMgrMalloc(char const *caller_name_val, char array_type_val, int max_array_size_val);
    void  arrayMgrFree(void *array_mgr_val);
    void  arrayMgrInsertElement(void *array_mgr_val, void *element_val);
    void  arrayMgrRemoveElement(void *array_mgr_val, void *element_val);
    void *arrayMgrGetArrayTable(void *array_mgr_val, int *array_size_ptr);
};
