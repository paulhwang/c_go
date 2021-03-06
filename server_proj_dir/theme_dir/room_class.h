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

class SessionClass;
class IdIndexListClass;
class ThemeClass;

class RoomClass : public ListEntryClass {
#define ROOM_CLASS_GROUP_ARRAY_SIZE 32
    ThemeClass *theThemeObject;
    char theBaseIdIndex[BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE + 4];
    char **theGroupTableArray;
    void *theGroupArrayMgr;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    RoomClass(void *list_mgr_object_val, ThemeClass *theme_object_val, char *group_id_index_val);
    ~RoomClass(void);
    char const* objectName(void) {return "RoomClass";}

    char *roomIdIndex(void) {return this->entryIdIndex();}
    char *baseIdIndex(void) {return this->theBaseIdIndex;}
    void setBaseIdIndex(char *base_id_index_val) {memcpy(this->theBaseIdIndex, base_id_index_val, BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE); this->theBaseIdIndex[BASE_MGR_PROTOCOL_BASE_ID_INDEX_SIZE] = 0;}
    void *groupArrayMgr(void) {return this->theGroupArrayMgr;}
    char *groupTableArray(int index_val) {return this->theGroupTableArray[index_val];}
    void setGroupTableArray(char ** val) {this->theGroupTableArray = val;}

    void insertGroup(char *group_id_index_val);
    void removeGroup(char *group_id_index_val);
};
