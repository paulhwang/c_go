/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.h
*/

#pragma once

class ListEntryClass;

class ListMgrClass {
#define LIST_MGR_ID_INDEX_ARRAY_SIZE 1000
#define LIST_MGR_MAX_GLOBAL_LIST_ID 9999
    void *theCallerObject;
    int theIdSize;
    int theIndexSize;
    int theIdIndexSize;

    int theGlobalEntryId;
    int theMaxIdIndexTableIndex;
    ListEntryClass *theEntryTableArray[LIST_MGR_ID_INDEX_ARRAY_SIZE];


    int allocEntryId(void);
    int allocEntryIndex(void);

    ListEntryClass *getEntryByIdIndex(int entry_id_val, int link_index_val);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class ListEntryClass;

public:
    ListMgrClass(void *caller_object_val, int id_size_val, int index_size_val);
    ~ListMgrClass(void);
    char const* objectName(void) {return "ListMgrClass";}

    ListEntryClass *mallocEntry(void *entry_data_val);
    void freeEntry(ListEntryClass *list_entry_object_val);
};
