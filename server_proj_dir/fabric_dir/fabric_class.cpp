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
