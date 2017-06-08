/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_mgr_class.h
*/

#pragma once
//#include "../../include_dir/protocol_dir/link_mgr_protocol.h"
class GroupClass;

class GroupMgrClass {
#define GROUP_MGR_GROUP_ARRAY_SIZE 1000
#define GROUP_MGR_MAX_GLOBAL_GROUP_ID 9999

    void *theMainObject;
    int theGlobalGroupId;
    GroupClass *theGroupTableArray[GROUP_MGR_GROUP_ARRAY_SIZE + 4];

    int allocGroupId(void);
    int allocGroupIndex(void);
    GroupClass *getGroupByIdIndex(int group_id_val, int group_index_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GroupMgrClass(void *main_object_val);
    ~GroupMgrClass(void);
    char const* objectName(void) {return "GroupMgrClass";}

    void mallocGroup(void);
    void freeGroup(GroupClass *group_object_val);

    void groupMgrLogit(char const* str0_val, char const* str1_val);
    void groupMgrAbend(char const* str0_val, char const* str1_val);
};
