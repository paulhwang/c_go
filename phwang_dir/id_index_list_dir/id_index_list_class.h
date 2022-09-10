/*
  Copyrights reserved
  Written by Paul Hwang
  File name: id_index_list_class.h
*/

#pragma once

class IdIndexListClass {
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

protected:

public:
    IdIndexListClass(void *caller_object_val, int id_size_val, int index_size_val);
    ~IdIndexListClass(void);
    char const* objectName(void) {return "IdIndexListClass";}

    void insertIdIndex(char *id_index_val);
    void removeIdIndex(char *id_index_val);
};
