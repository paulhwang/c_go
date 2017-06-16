/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.cpp
*/

#include "../../../../phwang_dir/phwang.h"
#include "session_mgr_class.h"
#include "link_mgr_class.h"
#include "link_class.h"
#include "../../fabric_class.h"

LinkMgrClass::LinkMgrClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(LinkMgrClass));
    this->theFabricObject = fabric_object_val;
    this->theGlobalLinkId = 0;

    if (1) {
        this->logit("LinkMgrClass", "init");
    }
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

void LinkMgrClass::mallocLink (char const *data_val)
{
    if (1) {
        this->logit("mallocLink", data_val);
    }
    int link_id = this->allocLinkId();
    int link_index = this->allocLinkIndex();
    if (link_index != -1) {
        this->theLinkTableArray[link_index] = new LinkClass(this, link_id, link_index, data_val);

        char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        data_buf[0] = LINK_MGR_PROTOCOL_RESPOND_IS_MALLOC_LINK;
        phwangEncodeIdIndex(data_buf + 1, link_id, LINK_MGR_PROTOCOL_LINK_ID_SIZE, link_index, LINK_MGR_PROTOCOL_LINK_INDEX_SIZE);

        this->theFabricObject->dFabricObject()->transmitFunction(data_buf);
    }
    else {
        /* TBD */
    }

/*
    int link_index = allocLinkIndex();
    LinkClass *link = new LinkClass(this, this->allocLinkId(), link_index, my_name_val);
    if (!link) {
        return 0;
    }

    return link;
    */
}

void LinkMgrClass::mallocSession (char *data_val)
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
        return;
    }
    link->sessionMgrObject()->mallocSession();
}

LinkClass *LinkMgrClass::getLinkByIdIndex(int link_id_val, int link_index_val)
{
    LinkClass *link = this->theLinkTableArray[link_index_val];
    if (!link) {
        this->abend("getLink", "null link");
        return 0;
    }

    if (link->linkId() != link_id_val){
        this->abend("getLink", "link id does not match");
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

