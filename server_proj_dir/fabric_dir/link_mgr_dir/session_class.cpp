/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "session_class.h"
#include "session_mgr_class.h"

SessionClass::SessionClass (SessionMgrClass *session_mgr_object_val, LinkClass *link_object_val)
    : ListEntryClass(session_mgr_object_val)
{
    this->theLinkObject = link_object_val;
    this->theSessionMgrObject = session_mgr_object_val;
    this->debug(true, "SessionClass", this->sessionIdIndex());
}

SessionClass::~SessionClass (void)
{
}

void SessionClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theSessionMgrObject->sessionMgrLogit(s, str1_val);
}

void SessionClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theSessionMgrObject->sessionMgrAbend(s, str1_val);
}
