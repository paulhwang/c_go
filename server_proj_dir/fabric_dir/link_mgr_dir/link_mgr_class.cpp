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

SessionClass *LinkMgrClass::mallocSession (char *data_val)
{
    int link_id;
    int link_index;
    if (1) {
        this->logit("mallocSession", data_val);
    }

    phwangDecodeIdIndex(data_val,
                &link_id,
                LINK_MGR_PROTOCOL_LINK_ID_SIZE,
                &link_index,
                LINK_MGR_PROTOCOL_LINK_INDEX_SIZE);
    data_val += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "link_id=%d link_index=%d", link_id, link_index);
        this->logit("mallocSession", s);
    }

    LinkClass *link = this->getLinkByIdIndex(link_id, link_index);
    if (!link) {
        return 0;
    }

    return link->mallocSession();
}

LinkClass *LinkMgrClass::searchLink (char *data_val)
{
    int link_id;
    int link_index;
    if (1) {
        this->logit("searchLink", data_val);
    }

    phwangDecodeIdIndex(data_val,
                &link_id,
                LINK_MGR_PROTOCOL_LINK_ID_SIZE,
                &link_index,
                LINK_MGR_PROTOCOL_LINK_INDEX_SIZE);
    //data_val += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "link_id=%d link_index=%d", link_id, link_index);
        this->logit("searchLink", s);
    }

    return this->getLinkByIdIndex(link_id, link_index);
}

SessionClass *LinkMgrClass::serachSession (char *data_val)
{
    LinkClass *link = searchLink(data_val);
    if (!link) {
        return 0;
    }

    return link->searchSession(data_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
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

void LinkMgrClass::freeLink (LinkClass *link_object_val)
{
    if (!link_object_val) {
        return;
    }
    link_object_val->~LinkClass();
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

