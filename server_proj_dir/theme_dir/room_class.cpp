/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/id_index_list_dir/id_index_list_class.h"
#include "../define_dir/ft_def.h"
#include "room_class.h"
#include "theme_class.h"

RoomClass::RoomClass (
    int debug_on_val,
    void *list_mgr_object_val,
    ThemeClass *theme_object_val,
    char *group_id_index_val):
        ListEntryClass(list_mgr_object_val),
        theThemeObject(theme_object_val)
{
    this->debugOn_ = true && debug_on_val;
    this->theGroupArrayMgr = phwangArrayMgrMalloc(this->debugOn_, this->objectName(), 's', 10);
    this->insertGroup(group_id_index_val);

    if (true && this->debugOn_) {
        printf("RoomClass::RoomClass() new_room=%s\n", this->roomIdIndex());
    }
}

RoomClass::~RoomClass (void)
{
    phwangDebugS(true, "RoomClass::~RoomClass", "exit");
}

void RoomClass::insertGroup (char *group_id_index_val)
{
    char buf[SIZE_DEF::GROUP_II_SIZE + 4];
    memcpy(buf, group_id_index_val, SIZE_DEF::GROUP_II_SIZE);
    buf[SIZE_DEF::GROUP_II_SIZE] = 0;
    phwangArrayMgrInsertElement(this->theGroupArrayMgr, buf);
}

void RoomClass::removeGroup (char *group_id_index_val)
{
    char buf[SIZE_DEF::GROUP_II_SIZE + 4];
    memcpy(buf, group_id_index_val, SIZE_DEF::GROUP_II_SIZE);
    buf[SIZE_DEF::GROUP_II_SIZE] = 0;
    phwangArrayMgrRemoveElement(this->theGroupArrayMgr, buf);
}
