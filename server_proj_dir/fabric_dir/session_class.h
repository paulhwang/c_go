/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.h
*/

#pragma once
#include "../../phwang_dir/list_mgr_dir/list_entry_class.h"
#include "../protocol_dir/session_mgr_protocol.h"

class LinkClass;
class GroupClass;

class SessionClass : public ListEntryClass {
    LinkClass *theLinkObject;
    GroupClass *theGroupObject;

    void bindGroup(GroupClass *group_object_val) {this->theGroupObject = group_object_val;}

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class UFabricClass;
    friend class DFabricClass;

    char *sessionIdIndex(void) {return this->theEntryIdIndex;}
    GroupClass *groupObject(void) {return this->theGroupObject;}

public:
    SessionClass(void *list_mgr_object_val, LinkClass *link_object_val);
    ~SessionClass(void);
    char const* objectName(void) {return "SessionClass";}
};