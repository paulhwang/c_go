/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.h
*/

#pragma once

#include "../../phwang_dir/list_mgr_dir/list_entry_class.h"
#include "../define_dir/size_def.h"

class LinkClass;
class GroupClass;

class SessionClass : public ListEntryClass {
    LinkClass *theLinkObject;
    GroupClass *theGroupObject;
    char theAjaxIdBuf[SIZE_DEF::AJAX_ID_SIZE + 1];
    char *theAjaxId;
    void *thePendingDownLinkDataQueue;

public:
    SessionClass(void *list_mgr_object_val, LinkClass *link_object_val);
    ~SessionClass(void);

    char const* objectName(void) {return "SessionClass";}
    char *ajaxId(void) {return this->theAjaxId;}
    void setAjaxId(char const *ajax_id_val) {strcpy(this->theAjaxIdBuf, ajax_id_val); this->theAjaxId = this->theAjaxIdBuf;}
    void resetAjaxId(void) {this->theAjaxId = 0;}
    char *sessionIdIndex(void) {return this->entryIdIndex();}
    LinkClass *linkObject(void) {return this->theLinkObject;}
    GroupClass *groupObject(void) {return this->theGroupObject;}
    void bindGroup(GroupClass *group_object_val) {this->theGroupObject = group_object_val;}
    char *getPendingDownLinkData(void) {return (char *) phwangDequeue(this->thePendingDownLinkDataQueue, "SessionClass::getPendingDownLinkData()");}
    void enqueuePendingDownLinkData(char *data_val);
};
