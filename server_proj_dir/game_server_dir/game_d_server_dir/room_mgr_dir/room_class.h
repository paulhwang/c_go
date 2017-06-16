/*
  Copyrights reserved
  Written by Paul Hwang
  File name: room_class.h
*/

#pragma once

class RoomMgrClass;
class SessionClass;

class RoomClass {
#define GROUP_SESSION_ARRAY_SIZE 32

    RoomMgrClass *theGroupMgrObject;
    int theGroupId;
    int theGroupIndex;
    SessionClass *theSessionTableArray[GROUP_SESSION_ARRAY_SIZE];

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    RoomClass(RoomMgrClass *group_mgr_object_val, int group_id_val, int group_index_val);
    ~RoomClass(void);
    char const* objectName(void) {return "RoomClass";}

    void insertSession(SessionClass *session_object_val);
    void removeSession(SessionClass *session_object_val);
};
