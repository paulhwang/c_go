/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "session_class.h"

SessionClass::SessionClass (ListMgrClass *list_mgr_object_val, LinkClass *link_object_val)
    : ListEntryClass(list_mgr_object_val)
{
    this->theLinkObject = link_object_val;
    this->debug(true, "SessionClass", this->sessionIdIndex());
}

SessionClass::~SessionClass (void)
{
}

void SessionClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void SessionClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
