/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_mgr_class.h
*/

#pragma once
#include "../../../protocol_dir/link_mgr_protocol.h"
class SessionClass;
class LinkClass;

class SessionMgrClass {
#define SESSION_MGR_SESSION_ARRAY_SIZE 1000
#define SESSION_MGR_MAX_GLOBAL_SESSION_ID 9999

    LinkClass *theLinkObject;
    int theGlobalSessionId;
    SessionClass *theSessionTableArray[SESSION_MGR_SESSION_ARRAY_SIZE + 4];

    int allocSessionId(void);
    int allocSessionIndex(void);
    SessionClass *getSessionByIdIndex(int session_id_val, int session_index_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    SessionMgrClass(LinkClass *link_object_val);
    ~SessionMgrClass(void);
    char const* objectName(void) {return "SessionMgrClass";}

    void mallocSession(void);
    void freeSession(SessionClass *session_object_val);

    void sessionMgrLogit(char const* str0_val, char const* str1_val);
    void sessionMgrAbend(char const* str0_val, char const* str1_val);
};
