/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.h
*/

#pragma once
#include "../../protocol_dir/session_mgr_protocol.h"

class SessionMgrClass;
class GroupClass;

class SessionClass {
    SessionMgrClass *theSessionMgrObject;
    int theSessionId;
    int theSessionIndex;
    char theSessionIdIndex[SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE + 4];
    GroupClass *theGroupObject;

    void bindGroup(GroupClass *group_object_val) {this->theGroupObject = group_object_val;}

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class UFabricClass;
    friend class DFabricClass;
    friend class SessionMgrClass;

    int sessionId(void) {return this->theSessionId;}
    int sessionIndex(void) {return this->theSessionIndex;}
    GroupClass *groupObject(void) {return this->theGroupObject;}

public:
    SessionClass(SessionMgrClass *session_mgr_object_val, int session_id_val, int session_index_val);
    ~SessionClass(void);
    char const* objectName(void) {return "SessionClass";}
};
