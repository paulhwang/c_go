/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.h
*/

#pragma once

class SessionMgrClass;

class SessionClass {
    SessionMgrClass *theSessionMgrObject;
    int theSessionId;
    int theSessionIndex;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    SessionClass(SessionMgrClass *session_mgr_object_val, int session_id_val, int session_index_val);
    ~SessionClass(void);
    char const* objectName(void) {return "SessionClass";}
};
