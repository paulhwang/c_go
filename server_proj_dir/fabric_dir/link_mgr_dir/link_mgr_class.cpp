/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "link_mgr_class.h"
#include "link_class.h"
#include "../fabric_class.h"
#include "../d_fabric_dir/d_fabric_class.h"

LinkMgrClass::LinkMgrClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(LinkMgrClass));
    this->theFabricObject = fabric_object_val;
    this->theGlobalLinkId = 100;

    this->debug(true, "LinkMgrClass", "init");
}

LinkMgrClass::~LinkMgrClass (void)
{
}

int LinkMgrClass::allocLinkId (void)
{
    if (this->theGlobalLinkId >= LINK_MGR_MAX_GLOBAL_LINK_ID) {
        this->theGlobalLinkId = 0;
    }
    this->theGlobalLinkId++;
    return this->theGlobalLinkId;
}

int LinkMgrClass::allocLinkIndex (void)
{
    int index = 0;
    while (index < LINK_MGR_LINK_ARRAY_SIZE) {
        if (!this->theLinkTableArray[index]) {
            return index;
        }
        index++;
    }
    return -1;
}

LinkClass *LinkMgrClass::getLinkByIdIndex (int link_id_val, int link_index_val)
{
    if (link_id_val > LINK_MGR_MAX_GLOBAL_LINK_ID) {
        this->abend("getSessionByIdIndex", "link_id_val too big");
        return 0;
    }

    if (link_index_val >= LINK_MGR_LINK_ARRAY_SIZE) {
        this->abend("getSessionByIdIndex", "link_index_val too big");
        return 0;
    }

    LinkClass *link = this->theLinkTableArray[link_index_val];
    if (!link) {
        this->abend("getLinkByIdIndex", "null link");
        return 0;
    }

    if (link->linkId() != link_id_val){
        this->abend("getLinkByIdIndex", "link id does not match");
        return 0;
    }

    return link;
}

void LinkMgrClass::linkMgrLogit (char const* str0_val, char const* str1_val) {
    phwangLogit(str0_val, str1_val);
}

void LinkMgrClass::linkMgrAbend (char const* str0_val, char const* str1_val) {
    phwangAbend(str0_val, str1_val);
}

void LinkMgrClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->linkMgrLogit(s, str1_val);
}

void LinkMgrClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->linkMgrAbend(s, str1_val);
}

