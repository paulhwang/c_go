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
    int debugOn_;
    LinkClass *linkObj_;
    GroupClass *groupObj_;
    //char theAjaxIdBuf[SIZE_DEF::AJAX_ID_SIZE + 1];
    //char *theAjaxId;
    void *pendingDataQueue_;

public:
    SessionClass(
        int debug_on_val,
        void *list_mgr_obj_val,
        LinkClass *link_obj_val);
    ~SessionClass(void);

    char const* objectName(void) {return "SessionClass";}
    //char *ajaxId(void) {return this->theAjaxId;}
    //void setAjaxId(char const *ajax_id_val) {strcpy(this->theAjaxIdBuf, ajax_id_val); this->theAjaxId = this->theAjaxIdBuf;}
    //void resetAjaxId(void) {this->theAjaxId = 0;}
    char *sessionIdIndex(void) {return this->entryIdIndex();}
    LinkClass *linkObject(void) {return this->linkObj_;}
    GroupClass *groupObject(void) {return this->groupObj_;}
    void bindGroup(GroupClass *group_obj_val) {this->groupObj_ = group_obj_val;}
    char *dequeuePendingData(void);
    void enqueuePendingData(char *data_val);
};
