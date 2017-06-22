/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_mgr_class.h
*/

#pragma once
#include "../../protocol_dir/room_mgr_protocol.h"
class RoomClass;
class ThemeClass;

class RoomMgrClass {
#define ROOM_MGR_ROOM_ARRAY_SIZE 1000
#define ROOM_MGR_MAX_GLOBAL_ROOM_ID 9999

    ThemeClass *theThemeObject;
    int theGlobalRoomId;
    RoomClass *theRoomTableArray[ROOM_MGR_ROOM_ARRAY_SIZE + 4];

    int allocRoomId(void);
    int allocRoomIndex(void);
    RoomClass *getRoomByIdIndex(int room_id_val, int room_index_val);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class UThemeClass;
    friend class DThemeClass;

    RoomClass *searchRoom(char *data_val);

public:
    RoomMgrClass(ThemeClass *theme_object_val);
    ~RoomMgrClass(void);
    char const* objectName(void) {return "RoomMgrClass";}

    RoomClass *mallocRoom(char *group_id_index_val);
    void freeRoom(RoomClass *group_object_val);

    void groupMgrLogit(char const* str0_val, char const* str1_val);
    void groupMgrAbend(char const* str0_val, char const* str1_val);
};
