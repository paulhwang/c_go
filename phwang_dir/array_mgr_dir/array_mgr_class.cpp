/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "array_mgr_class.h"

ArrayMgrClass::ArrayMgrClass(char const *caller_name_val, char array_type_val, int max_array_size_val):
        theCallerName(caller_name_val),
        theArrayType(array_type_val),
        theMaxArraySize(max_array_size_val),
        theArraySize(0)
{
    this->debug(true, "ArrayMgrClass", "init");
}

ArrayMgrClass::~ArrayMgrClass (void)
{
}

void ArrayMgrClass::insertElement(void *element_val)
{
    this->insertPointerElement(element_val);
}

void ArrayMgrClass::insertPointerElement(void *element_val)
{
    int i = 0;
    while (i < this->theArraySize) {
        if (!this->thePointerArrayTable[i]) {
            this->thePointerArrayTable[i] = element_val;
            return;
        }
        i++;
    }

    if (this->theArraySize < this->theMaxArraySize) {
        this->thePointerArrayTable[this->theArraySize] = element_val;
        this->theArraySize++;
        return;
    }

    this->abend("insertElement", "table is full");
}

void ArrayMgrClass::removeElement(void *element_val)
{
    this->removePointerElement(element_val);
}

void ArrayMgrClass::removePointerElement(void *element_val)
{
    int i = 0;
    while (i < this->theMaxArraySize) {
        if (this->thePointerArrayTable[i] == element_val) {
            this->thePointerArrayTable[i] = 0;
            return;
        }
        i++;
    }
    this->abend("removeElement", "not found");
}

void ArrayMgrClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s(%s)::%s", this->objectName(), this->theCallerName, str0_val);
    phwangLogit(s, str1_val);
}

void ArrayMgrClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s(%s)::%s", this->objectName(), this->theCallerName, str0_val);
    phwangAbend(s, str1_val);
}
