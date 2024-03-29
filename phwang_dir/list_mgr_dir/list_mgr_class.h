/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.h
*/

#pragma once
#include <pthread.h>

class ListEntryClass;

class ListMgrClass {
#define LIST_MGR_ID_INDEX_ARRAY_SIZE 1000
#define LIST_MGR_MAX_GLOBAL_LIST_ID 9999
    int debugOn_;
    char theObjectName[64];
    char const *theWho;
    int theIdSize;
    int theIndexSize;
    int theIdIndexSize;
    int theGlobalEntryId;
    int theMaxIdIndexTableIndex;
    int theMaxIndex;
    int theEntryCount;
    ListEntryClass *theEntryTableArray[LIST_MGR_ID_INDEX_ARRAY_SIZE];
    pthread_mutex_t theMutex;

    int allocEntryId(void);
    int allocEntryIndex(void);
    ListEntryClass *getEntryByIdIndex(int entry_id_val, int link_index_val, void *extra_data_val);
    void abendListMgrClass(char const *msg_val);

public:
    ListMgrClass(
        int debug_on_val,
        char const *caller_name_val,
        int id_size_val,
        int index_size_val,
        int global_entry_id_val);
    ~ListMgrClass(void);

    char *objectName(void) {return this->theObjectName;}
    int idSize(void) {return this->theIdSize;}
    int indexSize(void) {return this->theIndexSize;}
    int maxIndex(void) {return this->theMaxIndex;}
    ListEntryClass **entryTableArray(void) {return this->theEntryTableArray;}

    void insertEntry(ListEntryClass * entry_val);
    void removeEntry(ListEntryClass *list_entry_object_val);
    ListEntryClass *searchEntry(char const *data_val, void *extra_data_val);
};
