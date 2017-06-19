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

void SessionMgrClass::mallocSession (void)
{
    if (1) {
        this->logit("mallocSession", "");
    }
    int session_id = this->allocSessionId();
    int session_index = this->allocSessionIndex();
    if (session_index != -1) {
        this->theSessionTableArray[session_index] = new SessionClass(this, session_id, session_index);

        char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        data_buf[0] = LINK_MGR_PROTOCOL_RESPOND_IS_MALLOC_SESSION;
        phwangEncodeIdIndex(data_buf + 1, session_id, LINK_MGR_PROTOCOL_SESSION_ID_SIZE, session_index, LINK_MGR_PROTOCOL_SESSION_INDEX_SIZE);

        this->theLinkObject->linkMgrObject()->fabricObject()->dFabricObject()->transmitFunction(data_buf);
    }
    else {
        /* TBD */
    }
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

