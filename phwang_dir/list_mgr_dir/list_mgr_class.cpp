/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "list_mgr_class.h"
#include "list_entry_class.h"

ListMgrClass::ListMgrClass (void *caller_object_val, int id_size_val, int index_size_val)
{
    memset(this, 0, sizeof(ListMgrClass));
    this->theCallerObject = caller_object_val;
    this->theIdSize = id_size_val;
    this->theIndexSize = index_size_val;

    this->theGlobalEntryId = 0;
    this->theMaxIdIndexTableIndex = 0;

    this->debug(true, "ListMgrClass", "init");
}

ListMgrClass::~ListMgrClass (void)
{
}

int ListMgrClass::allocEntryId (void)
{
    if (this->theGlobalEntryId >= LIST_MGR_MAX_GLOBAL_LIST_ID) {
        this->theGlobalEntryId = 0;
    }
    this->theGlobalEntryId++;
    return this->theGlobalEntryId;
}

int ListMgrClass::allocEntryIndex (void)
{
    int index = 0;
    while (index < LIST_MGR_ID_INDEX_ARRAY_SIZE) {
        if (!this->theEntryTableArray[index]) {
            return index;
        }
        index++;
    }

    this->abend("allocEntryIndex", "out of entry_index");
    return -1;
}

ListEntryClass *ListMgrClass::mallocEntry(void *entry_data_val)
{
    this->debug(true, "mallocEntry", "");

    int entry_id = this->allocEntryId();
    int entry_index = this->allocEntryIndex();
    if (entry_index == -1) {
        return 0;
    }

    ListEntryClass *entry = new ListEntryClass(this, entry_id, entry_index, entry_data_val);
    this->theEntryTableArray[entry_index] = entry;
    return entry;
}

void ListMgrClass::freeEntry(ListEntryClass *list_entry_object_val)
{

}

void ListMgrClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ListMgrClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
