/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "list_mgr_class.h"

ListMgrClass::ListMgrClass (void *caller_object_val, int string_size_val)
{
    memset(this, 0, sizeof(ListMgrClass));
	this->theCallerObject = caller_object_val;
    this->theStringSize = string_size_val;

    if (1) {
        this->logit("ListMgrClass", "init");
    }

}

ListMgrClass::~ListMgrClass (void)
{

}

void ListMgrClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ListMgrClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
