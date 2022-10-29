/*
  Copyrights reserved
  Written by Paul Hwang
  File name: array_mgr_root_class.h
*/

#pragma once

class ArrayMgrRootClass
{
    char const *objectName(void) {return "ArrayMgrRootClass";}
    int theDebugCode;

public:
    ArrayMgrRootClass(int debug_code_val);
    ~ArrayMgrRootClass(void);
    
    void *arrayMgrMalloc(
        int debug_on_val,
        char const *who_val,
        char array_type_val,
        int max_array_size_val);
    void  arrayMgrFree(void *array_mgr_val);
    void  arrayMgrInsertElement(void *array_mgr_val, void *element_val);
    void  arrayMgrRemoveElement(void *array_mgr_val, void *element_val);
    void *arrayMgrGetArrayTable(void *array_mgr_val, int *array_size_ptr);
};
