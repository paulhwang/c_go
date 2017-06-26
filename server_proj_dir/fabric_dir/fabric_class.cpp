/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "fabric_class.h"
#include "u_fabric_dir/u_fabric_class.h"
#include "d_fabric_dir/d_fabric_class.h"
#include "group_class.h"
#include "link_class.h"

FabricClass::FabricClass (void)
{
    memset(this, 0, sizeof(FabricClass));
    this->theUFabricObject = new UFabricClass(this);
    this->theDFabricObject = new DFabricClass(this);
    this->theLinkListMgrObject = phwangListMgrMalloc("LINK", LINK_MGR_PROTOCOL_LINK_ID_SIZE, LINK_MGR_PROTOCOL_LINK_INDEX_SIZE, 100);
    this->theGroupListMgrObject = phwangListMgrMalloc("GROUP", GROUP_MGR_PROTOCOL_GROUP_ID_SIZE, GROUP_MGR_PROTOCOL_GROUP_INDEX_SIZE, 500);

    this->debug(true, "FabricClass", "init");
}

FabricClass::~FabricClass (void)
{
    this->theDFabricObject->~DFabricClass(); 
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
    this->debug(true, "mallocGroup", "");
    GroupClass *group = new GroupClass(this->theGroupListMgrObject, this);
    return group;
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
