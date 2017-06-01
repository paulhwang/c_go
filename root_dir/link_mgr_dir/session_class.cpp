/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.cpp
*/

#include <stdio.h>
#include <string.h>
#include "session_class.h"
#include "session_mgr_class.h"
#include "../../utils_dir/logit.h"

SessionClass::SessionClass (SessionMgrClass *session_mgr_object_val, int session_id_val)
{
    memset(this, 0, sizeof(SessionClass));
    this->theSessionMgrObject = session_mgr_object_val;
    this->theSessionId = session_id_val;

    if (1) {
        this->logit("SessionClass", "init");
    }
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
