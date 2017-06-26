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
    int i = 0;
    while (i < this->theMaxSessionTableArrayIndex) {
        if (!this->theSessionTableArray[i]) {
            this->theSessionTableArray[i] = session_object_val;
            return;
        }
        i++;
    }

    if (this->theMaxSessionTableArrayIndex < GROUP_CLASS_SESSION_ARRAY_SIZE) {
        this->theSessionTableArray[this->theMaxSessionTableArrayIndex] = session_object_val;
        this->theMaxSessionTableArrayIndex++;
        return;
    }

    this->abend("insertElement", "table is full");
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
