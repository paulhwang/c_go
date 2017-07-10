/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "fabric_class.h"
#include "u_fabric_dir/u_fabric_class.h"
#include "d_fabric_dir/d_fabric_class.h"
#include "group_class.h"
#include "link_class.h"
#include "name_list_class.h"

FabricClass::FabricClass (void)
{
    this->theUFabricObject = new UFabricClass(this);
    this->theDFabricObject = new DFabricClass(this);
    this->theNameListObject = new NameListClass(this);
    this->theLinkListMgrObject = phwangListMgrMalloc("LINK", LINK_MGR_PROTOCOL_LINK_ID_SIZE, LINK_MGR_PROTOCOL_LINK_INDEX_SIZE, 100);
    this->theGroupListMgrObject = phwangListMgrMalloc("GROUP", GROUP_MGR_PROTOCOL_GROUP_ID_SIZE, GROUP_MGR_PROTOCOL_GROUP_INDEX_SIZE, 500);
    printf("7777777777777777777theLinkListMgrObject: objectName=%s\n", ((ListMgrClass *) this->theLinkListMgrObject)->objectName());

    this->debug(true, "FabricClass", "init");
}

FabricClass::~FabricClass (void)
{
    this->theDFabricObject->~DFabricClass(); 
    this->theUFabricObject->~UFabricClass(); 
    this->theNameListObject->~NameListClass();
}

LinkClass *FabricClass::mallocLink (char const *data_val)
{
    this->debug(true, "mallocLink", data_val);
    LinkClass *link = new LinkClass(this->theLinkListMgrObject, this, data_val);
    this->theNameListObject->updateNameList();
    return link;
}

void FabricClass::freeLink (LinkClass *link_object_val)
{
    if (!link_object_val) {
        return;
    }
    link_object_val->~LinkClass();
    this->theNameListObject->updateNameList();
}

LinkClass *FabricClass::searchLinkByName (char *name_val)
{
    int max_index = phwnagListMgrGetMaxIndex(this->theLinkListMgrObject);
    LinkClass **link_entry_array = (LinkClass **) phwangListMgrGetEntryTableArray(this->theLinkListMgrObject);

    for (int i = max_index ; i >= 0; i--) {
        if (link_entry_array[i]) {
            if (!strcmp(link_entry_array[i]->linkName(), name_val)) {
                return link_entry_array[i];
            }
        }
    }
    return 0;
}

GroupClass *FabricClass::mallocGroup (char *theme_data_val)
{
    this->debug(true, "mallocGroup", "");
    GroupClass *group = new GroupClass(this->theGroupListMgrObject, this, theme_data_val);
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
