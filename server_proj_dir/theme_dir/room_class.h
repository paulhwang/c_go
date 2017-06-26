/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_class.h
*/

#pragma once
#include "../../phwang_dir/list_mgr_dir/list_entry_class.h"
#include "../protocol_dir/room_mgr_protocol.h"
#include "../protocol_dir/group_mgr_protocol.h"
#include "../protocol_dir/base_mgr_protocol.h"

class RoomMgrClass;
class SessionClass;
class IdIndexListClass;
class ThemeClass;

class RoomClass : public ListEntryClass {
#define ROOM_CLASS_GROUP_ARRAY_SIZE 32
    ThemeClass *theThemeObject;
    char theBaseIdIndex[BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE + 4];
    char *theGroupTableArray[ROOM_CLASS_GROUP_ARRAY_SIZE];
    int theMaxGroupTableArrayIndex;

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class UThemeClass;
    friend class DThemeClass;
    friend class RoomMgrClass;

    int roomId(void) {return this->theEntryId;}
    int roomIndex(void) {return this->theEntryIndex;}
    char *roomIdIndex(void) {return this->theEntryIdIndex;}
    void setBaseIdIndex(char *base_id_index_val) {memcpy(this->theBaseIdIndex, base_id_index_val, BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE); this->theBaseIdIndex[BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE] = 0;}
    void insertGroup(char *group_id_index_val);
    void removeGroup(char *group_id_index_val);

public:
    RoomClass(void *list_mgr_object_val, ThemeClass *theme_object_val, char *group_id_index_val);
    ~RoomClass(void);
    char const* objectName(void) {return "RoomClass";}
};
