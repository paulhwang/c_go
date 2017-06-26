/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "link_class.h"
#include "session_class.h"
#include "fabric_class.h"
  
LinkClass::LinkClass (void *list_mgr_object_val, FabricClass *fabric_object_val, char const* link_name_val):
        ListEntryClass(list_mgr_object_val),
        theFabricObject(fabric_object_val)
{
    if (strlen(link_name_val) <= LINK_CLASS_LINK_NAME_BUF_SIZE) {
        strcpy(this->theLinkName, link_name_val);
    }
    else {
        memcpy(this->theLinkName, link_name_val, LINK_CLASS_LINK_NAME_BUF_SIZE);
        this->theLinkName[LINK_CLASS_LINK_NAME_BUF_SIZE] = 0;
    }
    this->theSessionListMgrObject = phwangListMgrMalloc("SESSION", SESSION_MGR_PROTOCOL_SESSION_ID_SIZE, SESSION_MGR_PROTOCOL_SESSION_INDEX_SIZE, 300);

    this->debug(true, "LinkClass", this->linkIdIndex());
}

LinkClass::~LinkClass (void)
{
}

SessionClass *LinkClass::mallocSession (void)
{
    this->debug(true, "mallocSession", "");
    SessionClass *session = new SessionClass(this->theSessionListMgrObject, this);
    return session;
}

void LinkClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void LinkClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
