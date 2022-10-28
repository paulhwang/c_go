/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "../define_dir/fe_def.h"
#include "group_class.h"
#include "fabric_class.h"

GroupClass::GroupClass (
    int debug_on_val,
    void *list_mgr_object_val,
    FabricClass *fabric_object_val,
    char mode_val,
    char theme_type_val,
    char const *theme_info_val,
    char const *first_fiddle_val,
    char const *second_fiddle_val)
        :ListEntryClass(list_mgr_object_val)
{
    this->debugOn_ = true && debug_on_val;
    this->theFabricObject = fabric_object_val;
    this->theRoomStatus = FE_DEF::FE_ROOM_STATUS_PREPARING;
    this->theMode = mode_val;
    this->theThemeType = theme_type_val;
    this->theThemeInfo =    (char *) phwangMalloc(strlen(theme_info_val) + 1,     MallocClass::GroupClass);
    this->theFirstFiddle =  (char *) phwangMalloc(strlen(first_fiddle_val) + 1, MallocClass::GroupClass);
    this->theSecondFiddle = (char *) phwangMalloc(strlen(second_fiddle_val) + 1,      MallocClass::GroupClass);
    strcpy(this->theThemeInfo,    theme_info_val);
    strcpy(this->theFirstFiddle,  first_fiddle_val);
    strcpy(this->theSecondFiddle, second_fiddle_val);

    this->theSessionArrayMgr = phwangArrayMgrMalloc(this->objectName(), 'o', 10);
    this->theSessionTableArray = 0;

    if (true && this->debugOn_) {
        printf("GroupClass::GroupClass() new_group=%s\n", this->groupIdIndex());
    }
}

GroupClass::~GroupClass (void)
{
    phwangArrayMgrFree(this->theSessionArrayMgr);
    phwangFree(this->themeInfo());
    phwangFree(this->firstFiddle());
    phwangFree(this->secondFiddle());
}

void GroupClass::setRoomStatusToReady(void)
{
    this->theRoomStatus = FE_DEF::FE_ROOM_STATUS_READY;
}

int GroupClass::isDominatedGroup(void)
{
    if (this->mode() == FE_DEF::FE_GROUP_MODE_SOLO) {
        return 1;
    }
    else if (this->mode() == FE_DEF::FE_GROUP_MODE_ENSEMBLE) {
        return 1;
    }
    else if ((this->mode() == FE_DEF::FE_GROUP_MODE_DUET) &&
             (!strcmp(this->firstFiddle(), this->secondFiddle()))) {
        return 1;
    }
    else {
        return 0;
    }

}

