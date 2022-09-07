/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/abend_dir/abend_class.h"
#include "array_mgr_class.h"

ArrayMgrClass::ArrayMgrClass(char const *who_val, char array_type_val, int max_array_size_val):
        theWho(who_val),
        theArrayType(array_type_val),
        theMaxArraySize(max_array_size_val),
        theArraySize(0)
{
    this->allocArrayTable();
    this->debug(true, "ArrayMgrClass", "init");
}

ArrayMgrClass::~ArrayMgrClass (void)
{
}

void ArrayMgrClass::allocArrayTable (void)
{
    void *ptr;
    int i;
    char c;
    int size;

    switch (this->theArrayType) {
        case 'o': // object
        case 's': // string
            size = sizeof(ptr);
            break;

        case 'i': // integer
            size = sizeof(i);
            break;

        case 'c': // char
            size = sizeof(c);
            break;

        default:
            this->abend("allocArrayTable", "bad type");
            size = 16;
            break;
    }

    size *= this->theMaxArraySize;
    this->thePointerArrayTable = (void **) malloc(size);
}

void *ArrayMgrClass::getArrayTable (int *array_size_ptr)
{
    *array_size_ptr = this->theArraySize;

    switch (this->theArrayType) {
        case 'o': 
        case 's': 
            return this->thePointerArrayTable;

        case 'i':
        case 'c':
        default:
            this->abend("getArrayTable", "bad type");
            return 0;
    }
}

void ArrayMgrClass::insertElement(void *element_val)
{
    this->insertPointerElement(element_val);
}

void ArrayMgrClass::insertPointerElement(void *element_val)
{
    void *data;

    if (this->theArrayType == 's') {
        int len = strlen((char *) element_val);
        data = malloc(len + 4);
        strcpy((char *) data, (char *) element_val);
        this->logit("insertPointerElement", (char *) data);
    }
    else {
        data = element_val;
    }

    int i = 0;
    while (i < this->theArraySize) {
        if (!this->thePointerArrayTable[i]) {
            this->thePointerArrayTable[i] = data;
            return;
        }
        i++;
    }

    if (this->theArraySize < this->theMaxArraySize) {
        this->thePointerArrayTable[this->theArraySize] = data;
        this->theArraySize++;
        return;
    }

    this->abend("insertPointerElement", "table is full");
}

void ArrayMgrClass::removeElement(void *element_val)
{
    this->removePointerElement(element_val);
}

void ArrayMgrClass::removePointerElement(void *element_val)
{
    if (this->theArrayType == 's') {
        free(element_val);
    }

    int i = 0;
    while (i < this->theMaxArraySize) {
        if (this->thePointerArrayTable[i] == element_val) {
            this->thePointerArrayTable[i] = 0;
            return;
        }
        i++;
    }
    this->abend("removePointerElement", "not found");
}

void ArrayMgrClass::debug (int debug_on_val, char const *func_name_val, char const *str1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebug(debug_on_val, s, str1_val);
    }
}

void ArrayMgrClass::debug2 (int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebug2(debug_on_val, s, str1_val, str2_val);
    }
}

void ArrayMgrClass::debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebugInt(debug_on_val, s, str1_val, int1_val);
    }
}

void ArrayMgrClass::debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    if (debug_on_val) {
        char s[AbendClass::LogitFuncNameBufSize];
        this->composeFuncNameExtra(s, func_name_val);
        phwangDebugInt2(debug_on_val, s, str1_val, int1_val, str2_val, int2_val);
    }
}

void ArrayMgrClass::logit (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogit(s, str1_val);
}

void ArrayMgrClass::logit2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogit2(s, str1_val, str2_val);
}

void ArrayMgrClass::logitInt(char const *func_name_val, char const *str1_val, int int1_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogitInt(s, str1_val, int1_val);
}

void ArrayMgrClass::logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val)
{
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangLogitInt2(s, str1_val, int1_val, str2_val, int2_val);
}

void ArrayMgrClass::abend (char const *func_name_val, char const *str1_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangAbend(s, str1_val);
}

void ArrayMgrClass::abend2 (char const *func_name_val, char const *str1_val, char const *str2_val) {
    char s[AbendClass::LogitFuncNameBufSize];
    this->composeFuncNameExtra(s, func_name_val);
    phwangAbend2(s, str1_val, str2_val);
}
