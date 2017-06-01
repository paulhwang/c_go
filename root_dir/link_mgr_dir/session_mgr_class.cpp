/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_mgr_class.cpp
*/

#include <stdio.h>
#include <string.h>
#include "../../utils_dir/logit.h"
#include "session_mgr_class.h"

SessionMgrClass::SessionMgrClass (void *link_object_val)
{
    memset(this, 0, sizeof(SessionMgrClass));
    this->theLinkObject = link_object_val;
    this->theGlobalSessionId = 0;

    if (1) {
        this->logit("SessionMgrClass", "init");
    }
}

SessionMgrClass::~SessionMgrClass (void)
{
}

void SessionMgrClass::sessionMgrLogit (char const* str0_val, char const* str1_val) {
    LOGIT(str0_val, str1_val);
}

void SessionMgrClass::sessionMgrAbend (char const* str0_val, char const* str1_val) {
    LOGIT(str0_val, str1_val);
}

void SessionMgrClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->sessionMgrLogit(s, str1_val);
}

void SessionMgrClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->sessionMgrAbend(s, str1_val);
}

