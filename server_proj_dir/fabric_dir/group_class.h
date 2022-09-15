/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.h
*/

#pragma once
#include "../../phwang_dir/list_mgr_dir/list_entry_class.h"
#include "../define_dir/size_def.h"

class SessionClass;
class FabricClass;

class GroupClass : public ListEntryClass {
#define GROUP_CLASS_SESSION_ARRAY_SIZE 32
    FabricClass *theFabricObject;
    char theRoomIdIndex[SIZE_DEF::ROOM_ID_INDEX_SIZE + 4];
    void *theSessionArrayMgr;
    SessionClass **theSessionTableArray;

public:
    GroupClass(void *list_mgr_object_val, FabricClass *fabric_object_val, char *theme_data_val);
    ~GroupClass(void);
    char const* objectName(void) {return "GroupClass";}

    char *groupIdIndex(void) {return this->entryIdIndex();}
    char *roomIdIndex(void) {return this->theRoomIdIndex;}
    void *sessionArrayMgr(void) {return this->theSessionArrayMgr;}
    SessionClass *sessionTableArray(int index_val) {return this->theSessionTableArray[index_val];}
    void setSessionTableArray(SessionClass **val) {this->theSessionTableArray = val;}

    void setRoomIdIndex(char *val) {memcpy(this->theRoomIdIndex, val, SIZE_DEF::ROOM_ID_INDEX_SIZE);}
    void insertSession(SessionClass *session_object_val) {phwangArrayMgrInsertElement(this->theSessionArrayMgr, session_object_val);}
    void removeSession(SessionClass *session_object_val) {phwangArrayMgrRemoveElement(this->theSessionArrayMgr, session_object_val);}
};
