/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.h
*/

#pragma once
#include "../../phwang_dir/list_mgr_dir/list_entry_class.h"
#include "../protocol_dir/group_mgr_protocol.h"
#include "../protocol_dir/room_mgr_protocol.h"
#include "../protocol_dir/session_mgr_protocol.h"

class GroupMgrClass;
class SessionClass;
class FabricClass;

class GroupClass : public ListEntryClass {
#define GROUP_CLASS_SESSION_ARRAY_SIZE 32
    FabricClass *theFabricObject;
    GroupMgrClass *theGroupMgrObject;
    char theRoomIdIndex[ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE + 4];
    void *theSessionArrayMgr;
    SessionClass **theSessionTableArray;
    SessionClass *theSessionTableArray1[GROUP_CLASS_SESSION_ARRAY_SIZE];
    int theMaxSessionTableArrayIndex;

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class DFabricClass;
    friend class UFabricClass;
    friend class GroupMgrClass;

    int groupId(void) {return this->theEntryId;}
    int groupIndex(void) {return this->theEntryIndex;}
    char *groupIdIndex(void) {return this->theEntryIdIndex;}
    char *roomIdIndex(void) {return this->theRoomIdIndex;}
    void setRoomIdIndex(char *val) {memcpy(this->theRoomIdIndex, val, ROOM_MGR_PROTOCOL_ROOM_ID_INDEX_SIZE);}
    void insertSession(SessionClass *session_object_val);
    void removeSession(SessionClass *session_object_val);

public:
    GroupClass(void *list_mgr_object_val, FabricClass *fabric_object_val);
    ~GroupClass(void);
    char const* objectName(void) {return "GroupClass";}
};
