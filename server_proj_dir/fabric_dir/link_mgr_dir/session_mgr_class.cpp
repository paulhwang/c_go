/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_mgr_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "session_mgr_class.h"
#include "session_class.h"
#include "link_class.h"
#include "link_mgr_class.h"
#include "../fabric_class.h"
#include "../d_fabric_dir/d_fabric_class.h"

SessionMgrClass::SessionMgrClass (LinkClass *link_object_val)
{
    memset(this, 0, sizeof(SessionMgrClass));
    this->theLinkObject = link_object_val;
    this->theGlobalSessionId = 0;

    if (0) {
        this->logit("SessionMgrClass", "init");
    }
}

SessionMgrClass::~SessionMgrClass (void)
{
}

int SessionMgrClass::allocSessionId (void)
{
    if (this->theGlobalSessionId >= SESSION_MGR_MAX_GLOBAL_SESSION_ID) {
        this->theGlobalSessionId = 0;
    }
    this->theGlobalSessionId++;
    return this->theGlobalSessionId;
}

int SessionMgrClass::allocSessionIndex (void)
{
    int index = 0;
    while (index < SESSION_MGR_SESSION_ARRAY_SIZE) {
        if (!this->theSessionTableArray[index]) {
            return index;
        }
        index++;
    }
    return -1;
}

SessionClass *SessionMgrClass::mallocSession (void)
{
    if (1) {
        this->logit("mallocSession", "");
    }
    int session_id = this->allocSessionId();
    int session_index = this->allocSessionIndex();
    if (session_index != -1) {
        this->theSessionTableArray[session_index] = new SessionClass(this, session_id, session_index);
        return this->theSessionTableArray[session_index];
    }
    else {
        return 0;
    }
}

SessionClass *SessionMgrClass::searchSession (char *data_val)
{
    int session_id;
    int session_index;
    if (1) {
        this->logit("searchSession", data_val);
    }

    phwangDecodeIdIndex(data_val,
                &session_id,
                LINK_MGR_PROTOCOL_SESSION_ID_SIZE,
                &session_index,
                LINK_MGR_PROTOCOL_SESSION_INDEX_SIZE);

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "session_id=%d session_index=%d", session_id, session_index);
        this->logit("searchSession", s);
    }

    return this->getSessionByIdIndex(session_id, session_index);
}

SessionClass *SessionMgrClass::getSessionByIdIndex (int session_id_val, int session_index_val)
{
    if (session_id_val > SESSION_MGR_MAX_GLOBAL_SESSION_ID) {
        this->abend("getSessionByIdIndex", "session_id_val too big");
        return 0;
    }

    if (session_index_val >= SESSION_MGR_SESSION_ARRAY_SIZE) {
        this->abend("getSessionByIdIndex", "session_index_val too big");
        return 0;
    }

    SessionClass *session = this->theSessionTableArray[session_index_val];
    if (!session) {
        this->abend("getSessionByIdIndex", "null session");
        return 0;
    }

    if (session->sessionId() != session_id_val){
        this->abend("getSessionByIdIndex", "session id does not match");
        return 0;
    }

    return session;
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

