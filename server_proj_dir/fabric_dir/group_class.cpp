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
    void *list_mgr_object_val,
    FabricClass *fabric_object_val,
    char mode_val,
    char const *theme_info_val,
    char const *initiator_name_val,
    char const *peer_name_val)
        :ListEntryClass(list_mgr_object_val)
{
    this->theFabricObject = fabric_object_val;
    this->theRoomStatus = FE_DEF::FE_ROOM_STATUS_PREPARING;
    this->theMode = mode_val;
    this->theThemeInfo =     (char *) phwangMalloc(strlen(theme_info_val) + 1,     MallocClass::GroupClass);
    this->theInitiatorName = (char *) phwangMalloc(strlen(initiator_name_val) + 1, MallocClass::GroupClass);
    this->thePeerName =      (char *) phwangMalloc(strlen(peer_name_val) + 1,      MallocClass::GroupClass);
    strcpy(this->theThemeInfo,     theme_info_val);
    strcpy(this->theInitiatorName, initiator_name_val);
    strcpy(this->thePeerName,      peer_name_val);

    this->theSessionArrayMgr = phwangArrayMgrMalloc(this->objectName(), 'o', 10);
    this->theSessionTableArray = 0;

    phwangDebugSS(true, "GroupClass::GroupClass", "new_group:", this->groupIdIndex());
}

GroupClass::~GroupClass (void)
{
    phwangArrayMgrFree(this->theSessionArrayMgr);
    phwangFree(this->theThemeInfo);
    phwangFree(this->theInitiatorName);
    phwangFree(this->thePeerName);
}

void GroupClass::setRoomStatusToReady(void)
{
    this->theRoomStatus = FE_DEF::FE_ROOM_STATUS_READY;
}
