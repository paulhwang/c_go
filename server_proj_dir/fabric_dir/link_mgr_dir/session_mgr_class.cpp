/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_mgr_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../protocol_dir/session_mgr_protocol.h"
#include "session_mgr_class.h"
#include "session_class.h"
#include "link_class.h"
#include "link_mgr_class.h"
#include "../fabric_class.h"
#include "../d_fabric_dir/d_fabric_class.h"

SessionMgrClass::SessionMgrClass (LinkClass *link_object_val)
        : ListMgrClass(0, SESSION_MGR_PROTOCOL_SESSION_ID_SIZE, SESSION_MGR_PROTOCOL_SESSION_INDEX_SIZE, 300)
{
    this->debug(true, "SessionMgrClass", "init");
}

SessionMgrClass::~SessionMgrClass (void)
{
}

void SessionMgrClass::sessionMgrLogit (char const* str0_val, char const* str1_val) {
    phwangLogit(str0_val, str1_val);
}

void SessionMgrClass::sessionMgrAbend (char const* str0_val, char const* str1_val) {
    phwangAbend(str0_val, str1_val);
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

