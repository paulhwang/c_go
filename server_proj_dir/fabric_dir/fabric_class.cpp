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
#include "link_mgr_dir/link_class.h"

FabricClass::FabricClass (void)
{
    memset(this, 0, sizeof(FabricClass));
    this->theUFabricObject = new UFabricClass(this);
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
    this->theUFabricObject->~UFabricClass(); 
}

LinkClass *FabricClass::mallocLink (char const *data_val)
{
    this->debug(true, "mallocLink", data_val);
    LinkClass *link = new LinkClass(this->theLinkListMgrObject, this, data_val);
    return link;
}

void FabricClass::freeLink (LinkClass *link_object_val)
{
    if (!link_object_val) {
        return;
    }
    link_object_val->~LinkClass();
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

GroupClass *FabricClass::searchGroup (char *data_val)
{
    int group_id;
    int group_index;

    this->debug(true, "searchGroup", data_val);

    phwangDecodeIdIndex(data_val,
                &group_id,
                GROUP_MGR_PROTOCOL_GROUP_ID_SIZE,
                &group_index,
                GROUP_MGR_PROTOCOL_GROUP_INDEX_SIZE);

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "group_id=%d group_index=%d", group_id, group_index);
        this->logit("searchGroup", s);
    }

    return this->theGroupMgrObject->getGroupByIdIndex(group_id, group_index);
}

SessionClass *FabricClass::searchLinkAndMallocSession (char *data_val)
{
    LinkClass *link = this->searchLink(data_val);
    if (!link) {
        this->abend("searchLinkAndMallocSession", "null link");
        return 0;
    }

    return link->mallocSession();
}

SessionClass *FabricClass::serachLinkAndSession (char *data_val)
{
    LinkClass *link = this->searchLink(data_val);
    if (!link) {
        this->abend("serachLinkAndSession", "null link");
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
