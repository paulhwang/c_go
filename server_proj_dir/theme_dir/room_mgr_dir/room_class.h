/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_class.h
*/

#pragma once
#include "../../protocol_dir/group_mgr_protocol.h"

class RoomMgrClass;
class SessionClass;

class RoomClass {
#define GROUP_SESSION_ARRAY_SIZE 32

    RoomMgrClass *theRoomMgrObject;
    int theRoomId;
    int theRoomIndex;
    char theGroupIdIndex[GROUP_MGR_PROTOCOL_GROUP_ID_INDEX_SIZE + 4];
    SessionClass *theSessionTableArray[GROUP_SESSION_ARRAY_SIZE];

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class DThemeClass;
    friend class RoomMgrClass;

    int roomId(void) {return this->theRoomId;}
    int roomIndex(void) {return this->theRoomIndex;}
    char *groupIdIndex(void) {return this->theGroupIdIndex;}

public:
    RoomClass(RoomMgrClass *room_mgr_object_val, int room_id_val, int room_index_val, char *group_id_index_val);
    ~RoomClass(void);
    char const* objectName(void) {return "RoomClass";}

    void insertSession(SessionClass *session_object_val);
    void removeSession(SessionClass *session_object_val);
};
