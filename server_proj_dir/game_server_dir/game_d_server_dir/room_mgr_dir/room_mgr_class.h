/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_mgr_class.h
*/

#pragma once
#include "../../../protocol_dir/link_mgr_protocol.h"
class RoomClass;
class GameServerClass;

class RoomMgrClass {
#define GROUP_MGR_GROUP_ARRAY_SIZE 1000
#define GROUP_MGR_MAX_GLOBAL_GROUP_ID 9999

    GameServerClass *theGameServerObject;
    int theGlobalGroupId;
    RoomClass *theGroupTableArray[GROUP_MGR_GROUP_ARRAY_SIZE + 4];

    int allocGroupId(void);
    int allocGroupIndex(void);
    RoomClass *getGroupByIdIndex(int group_id_val, int group_index_val);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    RoomMgrClass(GameServerClass *game_server_object_val);
    ~RoomMgrClass(void);
    char const* objectName(void) {return "RoomMgrClass";}

    RoomClass *mallocGroup(void);
    void freeGroup(RoomClass *group_object_val);

    void groupMgrLogit(char const* str0_val, char const* str1_val);
    void groupMgrAbend(char const* str0_val, char const* str1_val);
};
