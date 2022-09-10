/*
  Copyrights reserved
  Written by Paul Hwang
  File name: array_mgr_root_class.cpp
*/

#include "../phwang.h"
#include "array_mgr_root_class.h"
#include "array_mgr_class.h"

ArrayMgrRootClass::ArrayMgrRootClass (int debug_code_val)
{
    memset(this, 0, sizeof (*this));
    this->theDebugCode = debug_code_val;
}

ArrayMgrRootClass::~ArrayMgrRootClass(void)
{
}

void *ArrayMgrRootClass::arrayMgrMalloc (char const *who_val, char array_type_val, int array_size_val)
{
    ArrayMgrClass *array_mgr = new ArrayMgrClass(who_val, array_type_val, array_size_val);
    return array_mgr;
}

void ArrayMgrRootClass::arrayMgrFree (void *array_mgr_val)
{
    if (!array_mgr_val) {
        phwangAbendS("ArrayMgrRootClass::arrayMgrFree", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        phwangAbendS("ArrayMgrRootClass::arrayMgrFree", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->~ArrayMgrClass();
}

void ArrayMgrRootClass::arrayMgrInsertElement (void *array_mgr_val, void *element_val)
{
    if (!array_mgr_val) {
        phwangAbendS("ArrayMgrRootClass::arrayMgrInsertElement", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        phwangAbendS("ArrayMgrRootClass::arrayMgrInsertElement", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->insertElement(element_val);
}

void ArrayMgrRootClass::arrayMgrRemoveElement (void *array_mgr_val, void *element_val)
{
    if (!array_mgr_val) {
        phwangAbendS("ArrayMgrRootClass::arrayMgrRemoveElement", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        phwangAbendS("ArrayMgrRootClass::arrayMgrRemoveElement", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->removeElement(element_val);
}

void *ArrayMgrRootClass::arrayMgrGetArrayTable (void *array_mgr_val, int *array_size_ptr)
{
    if (!array_mgr_val) {
        phwangAbendS("ArrayMgrRootClass::arrayMgrGetArrayTable", "null array_mgr_val");
        return 0;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        phwangAbendS("ArrayMgrRootClass::arrayMgrGetArrayTable", "wrong object");
        return 0;
    }

    return ((ArrayMgrClass *) array_mgr_val)->getArrayTable(array_size_ptr);
}
