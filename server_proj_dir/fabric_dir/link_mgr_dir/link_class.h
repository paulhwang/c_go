/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_class.h
*/

#pragma once
#include "../../protocol_dir/link_mgr_protocol.h"
#include "../../../phwang_dir/list_mgr_dir/list_mgr_class.h"

class LinkMgrClass;
class SessionMgrClass;
class SessionClass;
class ListMgrClass;

class LinkClass {
#define  LINK_CLASS_LINK_NAME_BUF_SIZE 32
    LinkMgrClass *theLinkMgrObject;
    int theLinkId;
    int theLinkIndex;
    char theLinkIdIndex[LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE + 4];
    char theLinkName[LINK_CLASS_LINK_NAME_BUF_SIZE + 4];
    //SessionMgrClass *theSessionMgrObject;
    ListMgrClass *theSessionListMgrObject;

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class LinkMgrClass;
    friend class SessionMgrClass;
    friend class DFabricClass;
    friend class UFabricClass;

    LinkMgrClass *linkMgrObject(void) {return this->theLinkMgrObject;}
    //SessionMgrClass *sessionMgrObject(void) {return this->theSessionMgrObject;}
    SessionClass *mallocSession(void);
    ListMgrClass *sessionListMgrObject(void) {return this->theSessionListMgrObject;}
    SessionClass *searchSession(char *data_val) {return (SessionClass *) this->theSessionListMgrObject->searchEntry(data_val);}

    int linkId(void) {return this->theLinkId;}
    int linkIndex(void) {return this->theLinkIndex;}
    char *linkIdIndex(void) {return this->theLinkIdIndex;}

public:
    LinkClass(LinkMgrClass *link_mgr_object_val, int link_id_val, int link_index_val, char const* link_name_val);
    ~LinkClass(void);
    char const* objectName(void) {return "LinkClass";}
};
