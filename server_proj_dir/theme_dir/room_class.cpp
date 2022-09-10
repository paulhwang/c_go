/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/id_index_list_dir/id_index_list_class.h"
#include "../protocol_dir/ft_command_class.h"
#include "room_class.h"
#include "theme_class.h"

RoomClass::RoomClass (void *list_mgr_object_val, ThemeClass *theme_object_val, char *group_id_index_val):
        ListEntryClass(list_mgr_object_val),
        theThemeObject(theme_object_val)
{
    this->theGroupArrayMgr = phwangArrayMgrMalloc(this->objectName(), 's', 10);
    this->insertGroup(group_id_index_val);

    phwangDebugSS(true, "RoomClass::RoomClass", "new_room:", this->roomIdIndex());
}

RoomClass::~RoomClass (void)
{
    phwangDebugS(true, "RoomClass::~RoomClass", "exit");
}

void RoomClass::insertGroup (char *group_id_index_val)
{
    char buf[FT_Command_Class::GROUP_ID_INDEX_SIZE + 4];
    memcpy(buf, group_id_index_val, FT_Command_Class::GROUP_ID_INDEX_SIZE);
    buf[FT_Command_Class::GROUP_ID_INDEX_SIZE] = 0;
    phwangArrayMgrInsertElement(this->theGroupArrayMgr, buf);
}

void RoomClass::removeGroup (char *group_id_index_val)
{
    char buf[FT_Command_Class::GROUP_ID_INDEX_SIZE + 4];
    memcpy(buf, group_id_index_val, FT_Command_Class::GROUP_ID_INDEX_SIZE);
    buf[FT_Command_Class::GROUP_ID_INDEX_SIZE] = 0;
    phwangArrayMgrRemoveElement(this->theGroupArrayMgr, buf);
}
