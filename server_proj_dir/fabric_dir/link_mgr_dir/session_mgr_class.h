/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_mgr_class.h
*/

#pragma once
#include "../../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "../../protocol_dir/link_mgr_protocol.h"

class SessionClass;
class LinkClass;

class SessionMgrClass : public ListMgrClass {
#define SESSION_MGR_SESSION_ARRAY_SIZE 1000
#define SESSION_MGR_MAX_GLOBAL_SESSION_ID 9999

    LinkClass *theLinkObject;
    int theGlobalSessionId;
    SessionClass *theSessionTableArray[SESSION_MGR_SESSION_ARRAY_SIZE + 4];

    int allocSessionId(void);
    int allocSessionIndex(void);
    SessionClass *getSessionByIdIndex(int session_id_val, int session_index_val);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class LinkMgrClass;
    friend class UFabricClass;

    LinkClass *linkObject(void) {return this->theLinkObject;}
    SessionClass *mallocSession(void);
    //void freeSession(SessionClass *session_object_val) {this->freeEntry(session_object_val);}
    SessionClass *searchSession(char *data_val) {return (SessionClass *) this->searchEntry(data_val);}

public:
    SessionMgrClass(LinkClass *link_object_val);
    ~SessionMgrClass(void);
    char const* objectName(void) {return "SessionMgrClass";}

    void sessionMgrLogit(char const* str0_val, char const* str1_val);
    void sessionMgrAbend(char const* str0_val, char const* str1_val);
};
