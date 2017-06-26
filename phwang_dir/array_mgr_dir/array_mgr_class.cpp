/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "array_mgr_class.h"

ArrayMgrClass::ArrayMgrClass(char const *caller_name_val, char array_type_val, int array_size_val):
        theCallerName(caller_name_val),
        theArrayType(array_type_val),
        theArraySize(array_size_val)
{
    this->debug(true, "ArrayMgrClass", "init");
}

ArrayMgrClass::~ArrayMgrClass (void)
{
}

void ArrayMgrClass::insertElement(void *element_val)
{

}

void ArrayMgrClass::removeElement(void *element_val)
{

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
