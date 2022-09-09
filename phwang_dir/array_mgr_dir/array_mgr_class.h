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

public:
    ArrayMgrClass(char const *who_val, char array_type_val, int max_array_size_val);
    ~ArrayMgrClass(void);
    char const* objectName(void) {return "ArrayMgrClass";}

    void *getArrayTable(int *array_size_ptr);
    void insertElement(void *element_val);
    void removeElement(void *element_val);
};
