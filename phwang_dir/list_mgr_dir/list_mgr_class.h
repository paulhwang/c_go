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
    char *theIdIndexTableArray[LIST_MGR_ID_INDEX_ARRAY_SIZE + 4];


    int allocEntryId(void);
    int allocLinkIndex(void);
    ListEntryClass *getEntryByIdIndex(int entry_id_val, int link_index_val);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:

public:
    ListMgrClass(void *caller_object_val, int id_size_val, int index_size_val);
    ~ListMgrClass(void);
    char const* objectName(void) {return "ListMgrClass";}

    void insertEntry(void *entry_val);
    void removeEntry(void *entry_val);
    void insertIdIndex(char *id_index_val);
    void removeIdIndex(char *id_index_val);
};
