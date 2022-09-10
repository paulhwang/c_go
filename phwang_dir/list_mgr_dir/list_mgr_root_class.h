/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_root_class.h
*/

#pragma once

class ListMgrRootClass
{
    char const *objectName(void) {return "ListMgrRootClass";}
    int theDebugCode;

public:
    ListMgrRootClass(int debug_code_val);
    ~ListMgrRootClass(void);
    
    void *listMgrMalloc(char const *who_val, int id_size_val, int index_size_val, int global_entry_id_val);
    void  listMgrFree(void *list_mgr_val);
    void listMgrRemoveEntry(void *list_mgr_val, void *entry_val);
    void *listMgrSearchEntry(void *list_mgr_val, char const *data_val, void *extra_data_val);
    int   listMgrGetMaxIndex(void *list_mgr_val, char const *who_val);
    void *listMgrGetEntryTableArray(void *list_mgr_val);
};
