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
    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class LinkMgrClass;
    friend class UFabricClass;


public:
    SessionMgrClass(LinkClass *link_object_val);
    ~SessionMgrClass(void);
    char const* objectName(void) {return "SessionMgrClass";}

    void sessionMgrLogit(char const* str0_val, char const* str1_val);
    void sessionMgrAbend(char const* str0_val, char const* str1_val);
};
