/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.h
*/

#pragma once

class GroupMgrClass;
class SessionClass;

class GroupClass {
#define GROUP_SESSION_ARRAY_SIZE 32

    GroupMgrClass *theGroupMgrObject;
    int theGroupId;
    int theGroupIndex;
    SessionClass *theSessionTableArray[GROUP_SESSION_ARRAY_SIZE];

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GroupClass(GroupMgrClass *group_mgr_object_val, int group_id_val, int group_index_val);
    ~GroupClass(void);
    char const* objectName(void) {return "GroupClass";}

    void insertSession(SessionClass *session_object_val);
    void removeSession(SessionClass *session_object_val);
};
