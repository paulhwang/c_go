/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "fabric_class.h"
#include "messenger_dir/messenger_class.h"
#include "../define_dir/fe_command_define.h"
#include "u_fabric_dir/u_fabric_class.h"
#include "d_fabric_dir/d_fabric_class.h"
#include "group_class.h"
#include "link_class.h"
#include "name_list_class.h"
#include "../db_dir/db_class.h"

FabricClass::FabricClass (int debug_code_val)
{
    memset(this, 0, sizeof(*this));
    this->theDebugCode = debug_code_val;
    
    this->theDbObject = new DbClass(this);
    this->theMessengerObject = new MessengerClass(this);
    this->theUFabricObject = new UFabricClass(this);
    this->theDFabricObject = new DFabricClass(this);
    this->theNameListObject = new NameListClass(this);
    this->theLinkListMgrObject = phwangListMgrMalloc("LINK", SIZE_DEF::LINK_ID_SIZE, SIZE_DEF::LINK_INDEX_SIZE, SIZE_DEF::LINK_ID_INITIAL_VALUE);
    this->theGroupListMgrObject = phwangListMgrMalloc("GROUP", SIZE_DEF::GROUP_ID_SIZE, SIZE_DEF::GROUP_INDEX_SIZE, SIZE_DEF::GROUP_ID_INITIAL_VALUE);
    this->startWatchDogThread();

    phwangDebugS(false, "FabricClass::FabricClass", "init");
}

FabricClass::~FabricClass (void)
{
    this->theDFabricObject->~DFabricClass(); 
    this->theUFabricObject->~UFabricClass(); 
    this->theNameListObject->~NameListClass();
    this->theDbObject->~DbClass();
    phwangDebugS(true, "~FabricClass::~FabricClass", "exit");
}

void FabricClass::linkKeepAliveExamine (void)
{
    if (1) {
        return;
    }
    
    int max_index = phwnagListMgrGetMaxIndex(this->theLinkListMgrObject, "FabricClass::linkKeepAliveExamine()");
    LinkClass **link_entry_array = (LinkClass **) phwangListMgrGetEntryTableArray(this->theLinkListMgrObject);

    for (int i = max_index ; i >= 0; i--) {
        LinkClass *link = link_entry_array[i];
        if (link && link->keepAliveTime() && link->keepAliveTimerExpired()) {
            if (1) { /* debug */
                char s[128];
                sprintf(s, "(***link expired***) linkName=%s linkIdIndex=%s", link->linkName(), link->linkIdIndex());
                phwangLogitS("FabricClass::linkKeepAliveExamine", s);
            }
            phwangListMgrRemoveEntry(this->theLinkListMgrObject, link);
            delete link;
        }
    }

}

LinkClass *FabricClass::mallocLink (char const *data_val)
{
    phwangDebugSS(false, "FabricClass::mallocLink", "data", data_val);

    if (strcmp(((ListMgrClass *) this->linkListMgrObject())->objectName(), "ListMgrClass")) {
        phwangAbendS("abricClass::mallocLink", "bad name 000");
    }

    LinkClass *link = new LinkClass(this->theLinkListMgrObject, this, data_val);
    if (!link) {
        phwangAbendS("FabricClass::mallocLink", "fail_to_malloc_link");
        return 0;
    }

    if (strcmp(((ListMgrClass *) this->linkListMgrObject())->objectName(), "ListMgrClass")) {
        phwangAbendS("abricClass::mallocLink", "bad name 111");
    }

    this->theNameListObject->updateNameList();
    return link;
}

void FabricClass::freeLink (LinkClass *link_object_val)
{
    phwangDebugS(true, "FabricClass::freeLink", link_object_val->linkIdIndex());
    if (!link_object_val) {
        return;
    }

    if (strcmp(((ListMgrClass *) this->linkListMgrObject())->objectName(), "ListMgrClass")) {
        phwangAbendS("FabricClass::freeLink", "bad name 000");
    }

    link_object_val->~LinkClass();

    if (strcmp(((ListMgrClass *) this->linkListMgrObject())->objectName(), "ListMgrClass")) {
        phwangAbendS("FabricClass::freeLink", "bad name 111");
    }

    this->theNameListObject->updateNameList();
}

LinkClass *FabricClass::searchLinkByName (char *name_val)
{
    int max_index = phwnagListMgrGetMaxIndex(this->theLinkListMgrObject, "FabricClass::searchLinkByName()");
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
    GroupClass *group = new GroupClass(this->theGroupListMgrObject, this, theme_data_val);
    if (!group) {
        phwangAbendS("FabricClass::mallocGroup", "fail_to_malloc_group");
        return 0;
    }
    return group;
}

SessionClass *FabricClass::serachLinkAndSession (char *data_val)
{
    LinkClass *link = this->searchLink(data_val, 0);
    if (!link) {
        phwangAbendS("FabricClass::serachLinkAndSession", "null link");
        return 0;
    }

    return link->searchSession(data_val + SIZE_DEF::LINK_ID_INDEX_SIZE);
}
