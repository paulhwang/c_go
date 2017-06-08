/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_class.h
*/

#pragma once

class GroupMgrClass;

class GroupClass {
    GroupMgrClass *theGroupMgrObject;
    int theGroupId;
    int theGroupIndex;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GroupClass(GroupMgrClass *group_mgr_object_val, int group_id_val, int group_index_val);
    ~GroupClass(void);
    char const* objectName(void) {return "GroupClass";}
};
