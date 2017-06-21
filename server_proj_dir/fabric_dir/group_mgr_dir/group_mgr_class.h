/*
  Copyrights reserved
  Written by Paul Hwang
  File name: group_mgr_class.h
*/

#pragma once
#include "../../protocol_dir/group_mgr_protocol.h"
class GroupClass;
class FabricClass;

class GroupMgrClass {
#define GROUP_MGR_GROUP_ARRAY_SIZE 1000
#define GROUP_MGR_MAX_GLOBAL_GROUP_ID 9999

    FabricClass *theFabricObject;
    int theGlobalGroupId;
    GroupClass *theGroupTableArray[GROUP_MGR_GROUP_ARRAY_SIZE + 4];

    int allocGroupId(void);
    int allocGroupIndex(void);
    GroupClass *getGroupByIdIndex(int group_id_val, int group_index_val);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    GroupClass *searchGroup(char *data_val);

public:
    GroupMgrClass(FabricClass *fabric_object_val);
    ~GroupMgrClass(void);
    char const* objectName(void) {return "GroupMgrClass";}

    GroupClass *mallocGroup(void);
    void freeGroup(GroupClass *group_object_val);

    void groupMgrLogit(char const* str0_val, char const* str1_val);
    void groupMgrAbend(char const* str0_val, char const* str1_val);
};
