/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "../../phwang_dir/file_dir/file_mgr_class.h"
#include "fabric_class.h"
#include "messenger_dir/messenger_class.h"
#include "../define_dir/fe_def.h"
#include "u_fabric_dir/u_fabric_class.h"
#include "d_fabric_dir/d_fabric_class.h"
#include "group_class.h"
#include "link_class.h"
#include "name_list_class.h"
#include "../db_dir/db_class.h"

FabricClass::FabricClass (int debug_on_val)
{
    memset(this, 0, sizeof(*this));
    this->debugOn_ = true && debug_on_val;
    this->theDebugCode = debug_on_val;
    
    this->fileMgrObj_ = new FileMgrClass(this->debugOn_);
    this->theDbObject = new DbClass(this);
    this->theMessengerObject = new MessengerClass(this);
    this->theUFabricObject = new UFabricClass(this->debugOn_, this);
    this->theDFabricObject = new DFabricClass(this->debugOn_, this);
    this->theNameListObject = new NameListClass(this->debugOn_, this);
    this->theLinkListMgrObject = phwangListMgrMalloc(this->debugOn_, "LINK", SIZE_DEF::LINK_ID_SIZE, SIZE_DEF::LINK_INDEX_SIZE, SIZE_DEF::LINK_ID_INITIAL_VALUE);
    this->theGroupListMgrObject = phwangListMgrMalloc(this->debugOn_, "GROUP", SIZE_DEF::GROUP_ID_SIZE, SIZE_DEF::GROUP_INDEX_SIZE, SIZE_DEF::GROUP_ID_INITIAL_VALUE);
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
                sprintf(s, "(***link expired***) myName=%s linkIdIndex=%s", link->myName(), link->linkIdIndex());
                phwangLogitS("FabricClass::linkKeepAliveExamine", s);
            }
            phwangListMgrRemoveEntry(this->theLinkListMgrObject, link);
            delete link;
        }
    }

}

LinkClass *FabricClass::mallocLink (
    char const *my_name_val,
    char device_type_val,
    void *port_object_val)
{
    phwangDebugSS(false, "FabricClass::mallocLink", "my_name_val", my_name_val);

    if (strcmp(((ListMgrClass *) this->linkListMgrObject())->objectName(), "ListMgrClass")) {
        phwangAbendS("abricClass::mallocLink", "bad name 000");
    }

    LinkClass *link = new LinkClass(this->debugOn_, this->theLinkListMgrObject, this, my_name_val, device_type_val, port_object_val);
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
    if (true && this->debugOn_) {
        printf("FabricClass::freeLink() id=%s\n", link_object_val->linkIdIndex());
    }

    if (!link_object_val) {
        return;
    }

    if (strcmp(((ListMgrClass *) this->linkListMgrObject())->objectName(), "ListMgrClass")) {
        phwangAbendS("FabricClass::freeLink", "bad name 000");
    }

    delete link_object_val;
    //link_object_val->~LinkClass();

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
            if (!strcmp(link_entry_array[i]->myName(), name_val)) {
                return link_entry_array[i];
            }
        }
    }
    return 0;
}

GroupClass *FabricClass::mallocGroup (
    char mode_val,
    char theme_type_val,
    char const *theme_info_val,
    char const *initiator_name_val,
    char const *peer_name_val)
{
    GroupClass *group = new GroupClass(this->debugOn_, this->theGroupListMgrObject, this, mode_val, theme_type_val, theme_info_val, initiator_name_val, peer_name_val);
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

    return link->searchSession(data_val + SIZE_DEF::LINK_II_SIZE);
}
