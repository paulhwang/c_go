/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "../../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "link_class.h"
#include "session_mgr_class.h"
#include "session_class.h"
#include "link_mgr_class.h"

LinkClass::LinkClass (LinkMgrClass *link_mgr_object_val, int link_id_val, int link_index_val, char const* link_name_val)
{
    memset(this, 0, sizeof(LinkClass));
    this->theLinkMgrObject = link_mgr_object_val;
    this->theLinkId = link_id_val;
    this->theLinkIndex = link_index_val;
    phwangEncodeIdIndex(this->theLinkIdIndex, this->theLinkId, LINK_MGR_PROTOCOL_LINK_ID_SIZE, this->theLinkIndex, LINK_MGR_PROTOCOL_LINK_INDEX_SIZE);

    if (strlen(link_name_val) <= LINK_CLASS_LINK_NAME_BUF_SIZE) {
        strcpy(this->theLinkName, link_name_val);
    }
    else {
        memcpy(this->theLinkName, link_name_val, LINK_CLASS_LINK_NAME_BUF_SIZE);
        this->theLinkName[LINK_CLASS_LINK_NAME_BUF_SIZE] = 0;
    }
    this->theSessionMgrObject = new SessionMgrClass(this);

    this->debug(true, "LinkClass", this->theLinkIdIndex);
}

LinkClass::~LinkClass (void)
{
}

SessionClass *LinkClass::mallocSession (void)
{
    this->debug(true, "mallocSession", "");
    SessionClass *session = new SessionClass(this->theSessionMgrObject, this);
    return session;
}

void LinkClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theLinkMgrObject->linkMgrLogit(s, str1_val);
}

void LinkClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theLinkMgrObject->linkMgrAbend(s, str1_val);
}
