/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "list_mgr_class.h"
#include "list_entry_class.h"

ListMgrClass::ListMgrClass (void *caller_object_val, int id_size_val, int index_size_val, int global_entry_id_val)
        : theIdSize(id_size_val),
          theIndexSize(index_size_val),
          theGlobalEntryId(global_entry_id_val)
{
    //memset(this, 0, sizeof(ListMgrClass));
    this->theCallerObject = caller_object_val;

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

void ListMgrClass::insertEntry (ListEntryClass * entry_val)
{
    this->debug(true, "InsertEntry", "");

    entry_val->theEntryId = this->allocEntryId();
    entry_val->theEntryIndex = this->allocEntryIndex();
    if (entry_val->theEntryIndex != -1) {
        phwangEncodeIdIndex(entry_val->theEntryIdIndex, entry_val->theEntryId, this->theIdSize, entry_val->theEntryIndex, this->theIndexSize);
        this->theEntryTableArray[entry_val->theEntryIndex] = entry_val;
        return;
    }

    this->abend("InsertEntry", "TBD");
}

/*
ListEntryClass *ListMgrClass::mallocEntry(void)
{
    this->debug(true, "mallocEntry", "");

    int entry_id = this->allocEntryId();
    int entry_index = this->allocEntryIndex();
    if (entry_index == -1) {
        return 0;
    }

    ListEntryClass *entry = new ListEntryClass(this, entry_id, entry_index, 0, this->theIdSize, this->theIndexSize);
    this->theEntryTableArray[entry_index] = entry;
    return entry;
}
*/

void ListMgrClass::freeEntry (ListEntryClass *list_entry_object_val)
{

}

ListEntryClass *ListMgrClass::searchEntry (char *data_val)
{
    int entry_id;
    int entry_index;

    this->debug(true, "searchEntry", data_val);

    phwangDecodeIdIndex(data_val, &entry_id, this->theIdSize, &entry_index, this->theIndexSize);

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "entry_id=%d entry_index=%d", entry_id, entry_index);
        this->logit("searchEntry", s);
    }

    return this->getEntryByIdIndex(entry_id, entry_index);
}

ListEntryClass *ListMgrClass::getEntryByIdIndex (int entry_id_val, int link_index_val)
{
    if (entry_id_val > LIST_MGR_MAX_GLOBAL_LIST_ID) {
        this->abend("getEntryByIdIndex", "entry_id_val too big");
        return 0;
    }

    if (link_index_val >= LIST_MGR_MAX_GLOBAL_LIST_ID) {
        this->abend("getEntryByIdIndex", "link_index_val too big");
        return 0;
    }

    ListEntryClass *entry = this->theEntryTableArray[link_index_val];
    if (!entry) {
        this->abend("getEntryByIdIndex", "null entry");
        return 0;
    }

    if (entry->theEntryId != entry_id_val){
        this->abend("getEntryByIdIndex", "entry id does not match");
        return 0;
    }

    return entry;
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
