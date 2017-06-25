/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "fabric_class.h"
#include "u_fabric_dir/u_fabric_class.h"
#include "d_fabric_dir/d_fabric_class.h"
#include "group_mgr_dir/group_mgr_class.h"
#include "group_mgr_dir/group_class.h"
#include "link_mgr_dir/link_mgr_class.h"
#include "link_mgr_dir/link_class.h"

FabricClass::FabricClass (void)
{
    memset(this, 0, sizeof(FabricClass));
    this->theUFabricObject = new UFabricClass(this);
    this->theLinkMgrObject = new LinkMgrClass(this);
    this->theGroupMgrObject = new GroupMgrClass(this);
    this->theDFabricObject = new DFabricClass(this);
    this->theLinkListMgrObject = phwangMallocListMgr("LINK", LINK_MGR_PROTOCOL_LINK_ID_SIZE, LINK_MGR_PROTOCOL_LINK_INDEX_SIZE, 100);
    this->theGroupListMgrObject = phwangMallocListMgr("GROUP", GROUP_MGR_PROTOCOL_GROUP_ID_SIZE, GROUP_MGR_PROTOCOL_GROUP_INDEX_SIZE, 500);

    this->debug(true, "FabricClass", "init");
}

FabricClass::~FabricClass (void)
{
    this->theDFabricObject->~DFabricClass(); 
    this->theGroupMgrObject->~GroupMgrClass(); 
    this->theLinkMgrObject->~LinkMgrClass(); 
    this->theUFabricObject->~UFabricClass(); 
}

LinkClass *FabricClass::mallocLink (char const *data_val)
{
    this->debug(true, "mallocLink", data_val);

    int link_id = this->theLinkMgrObject->allocLinkId();
    int link_index = this->theLinkMgrObject->allocLinkIndex();
    if (link_index != -1) {
        this->theLinkMgrObject->theLinkTableArray[link_index] = new LinkClass(this->theLinkMgrObject, this, link_id, link_index, data_val);
        return this->theLinkMgrObject->theLinkTableArray[link_index];
    }
    else {
        return 0;
    }
}

GroupClass *FabricClass::mallocGroup (void)
{
    if (1) {
        this->logit("mallocGroup", "");
    }
    int group_id = this->theGroupMgrObject->allocGroupId();
    int group_index = this->theGroupMgrObject->allocGroupIndex();
    if (group_index != -1) {
        GroupClass *group = new GroupClass(this->theGroupMgrObject, this, group_id, group_index);
        this->theGroupMgrObject->theGroupTableArray[group_index] = group;
        return group;
    }
    else {
        /* TBD */
    }
}

SessionClass *FabricClass::mallocSession (char *data_val)
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

    LinkClass *link = this->theLinkMgrObject->getLinkByIdIndex(link_id, link_index);
    if (!link) {
        return 0;
    }

    return link->mallocSession();
}

SessionClass *FabricClass::serachSession (char *data_val)
{
    LinkClass *link = this->theLinkMgrObject->searchLink(data_val);
    if (!link) {
        return 0;
    }

    return link->searchSession(data_val + LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE);
}

void FabricClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void FabricClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
