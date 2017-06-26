/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/id_index_list_dir/id_index_list_class.h"
#include "room_class.h"
#include "theme_class.h"

RoomClass::RoomClass (void *list_mgr_object_val, ThemeClass *theme_object_val, char *group_id_index_val):
        ListEntryClass(list_mgr_object_val),
        theThemeObject(theme_object_val)
{
    this->theGroupArrayMgr = phwangArrayMgrMalloc(this->objectName(), 's', 10);
    this->insertGroup(group_id_index_val);

    this->debug(true, "RoomClass", this->roomIdIndex());
}

RoomClass::~RoomClass (void)
{
}

void RoomClass::insertGroup (char *group_id_index_val)
{
    char buf[GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE + 4];
    memcpy(buf, group_id_index_val, GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    buf[GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE] = 0;
    phwangArrayMgrInsertElement(this->theGroupArrayMgr, buf);
}

void RoomClass::removeGroup (char *group_id_index_val)
{
    char buf[GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE + 4];
    memcpy(buf, group_id_index_val, GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE);
    buf[GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE] = 0;
    phwangArrayMgrRemoveElement(this->theGroupArrayMgr, buf);
}

void RoomClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void RoomClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
