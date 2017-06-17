/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.h
*/

#pragma once

class ListEntryClass;

class ListMgrClass {
#define LIST_MGR_ENTRY_ARRAY_SIZE 1000
#define LIST_MGR_MAX_GLOBAL_LIST_ID 9999
    void *theCallerObject;
    int theStringSize;
    int theGlobalEntryId;
    ListEntryClass *theEntryTableArray[LIST_MGR_ENTRY_ARRAY_SIZE + 4];

    int allocEntryId(void);
    int allocLinkIndex(void);
    ListEntryClass *getEntryByIdIndex(int entry_id_val, int link_index_val);

    void debug(int on_off_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    ListMgrClass(void *caller_object_val, int string_size_val);
    ~ListMgrClass(void);
    char const* objectName(void) {return "ListMgrClass";}
};
