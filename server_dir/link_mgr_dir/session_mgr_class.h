/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_mgr_class.h
*/

#pragma once

class SessionMgrClass {
    void *theLinkObject;
    int theGlobalSessionId;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    SessionMgrClass(void *link_object_val);
    ~SessionMgrClass();
    char const* objectName(void) {return "SessionMgrClass";}

    void sessionMgrLogit(char const* str0_val, char const* str1_val);
    void sessionMgrAbend(char const* str0_val, char const* str1_val);
};
