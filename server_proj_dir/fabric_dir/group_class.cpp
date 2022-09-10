/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/list_mgr_dir/list_mgr_class.h"
#include "group_class.h"
#include "fabric_class.h"

GroupClass::GroupClass (void *list_mgr_object_val, FabricClass *fabric_object_val, char *theme_data_val):
        ListEntryClass(list_mgr_object_val),
        theFabricObject(fabric_object_val)
{
    this->theSessionArrayMgr = phwangArrayMgrMalloc(this->objectName(), 'o', 10);
    this->theSessionTableArray = 0;

    phwangDebugS(true, "GroupClass::GroupClass", this->groupIdIndex());
}

GroupClass::~GroupClass (void)
{
    phwangArrayMgrFree(this->theSessionArrayMgr);
}
