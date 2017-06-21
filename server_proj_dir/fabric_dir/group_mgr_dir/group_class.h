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
    void *theSessionCallbackObject;

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class DFabricClass;
    friend class GroupMgrClass;

    int groupId(void) {return this->theGroupId;}
    int groupIndex(void) {return this->theGroupIndex;}

    void insertSession(SessionClass *session_object_val);
    void removeSession(SessionClass *session_object_val);
    void transmitToTheme(void *data_val, void *session_object_val);

public:
    GroupClass(GroupMgrClass *group_mgr_object_val, int group_id_val, int group_index_val);
    ~GroupClass(void);
    char const* objectName(void) {return "GroupClass";}
};
