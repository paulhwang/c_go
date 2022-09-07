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

void *ArrayMgrRootClass::arrayMgrMalloc(char const *who_val, char array_type_val, int array_size_val)
{
    ArrayMgrClass *array_mgr = new ArrayMgrClass(who_val, array_type_val, array_size_val);
    return array_mgr;
}

void ArrayMgrRootClass::arrayMgrFree(void *array_mgr_val)
{
    if (!array_mgr_val) {
        this->abend("arrayMgrFree", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        this->abend("arrayMgrFree", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->~ArrayMgrClass();
}

void ArrayMgrRootClass::arrayMgrInsertElement(void *array_mgr_val, void *element_val)
{
    if (!array_mgr_val) {
        this->abend("arrayMgrInsertElement", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        this->abend("arrayMgrInsertElement", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->insertElement(element_val);
}

void ArrayMgrRootClass::arrayMgrRemoveElement(void *array_mgr_val, void *element_val)
{
    if (!array_mgr_val) {
        this->abend("arrayMgrRemoveElement", "null array_mgr_val");
        return;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        this->abend("arrayMgrRemoveElement", "wrong object");
        return;
    }

    ((ArrayMgrClass *) array_mgr_val)->removeElement(element_val);
}

void *ArrayMgrRootClass::arrayMgrGetArrayTable(void *array_mgr_val, int *array_size_ptr)
{
    if (!array_mgr_val) {
        this->abend("arrayMgrGetArrayTable", "null array_mgr_val");
        return 0;
    }

    if (strcmp(((ArrayMgrClass *) array_mgr_val)->objectName(), "ArrayMgrClass")) {
        this->abend("arrayMgrGetArrayTable", "wrong object");
        return 0;
    }

    return ((ArrayMgrClass *) array_mgr_val)->getArrayTable(array_size_ptr);
}

void ArrayMgrRootClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ArrayMgrRootClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
