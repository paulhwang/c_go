/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "list_mgr_class.h"
#include "list_entry_class.h"

ListMgrClass::ListMgrClass (
    int debug_on_val,
    char const *who_val,
    int id_size_val,
    int index_size_val,
    int global_entry_id_val)
{
    memset(this, 0, sizeof(ListMgrClass));
    this->debugOn_ = true && debug_on_val;
    this->theWho = who_val;
    this->theIdSize = id_size_val;
    this->theIndexSize = index_size_val;
    this->theGlobalEntryId = global_entry_id_val;
    this->theEntryCount = 0;
    this->theMaxIdIndexTableIndex = 0;
    this->theMaxIndex = 0;
    //this->theMutex = PTHREAD_MUTEX_INITIALIZER;

    if (pthread_mutex_init(&this->theMutex, NULL) != 0) {
        phwangAbendWS("ListMgrClass::ListMgrClass", this->theWho, "pthread_mutex_init fail");
    }

    strcpy(this->theObjectName, "ListMgrClass");
    for (int i = 0; i < LIST_MGR_ID_INDEX_ARRAY_SIZE; i++) {
        theEntryTableArray[i] = 0;
    }

    phwangDebugWS(false, "ListMgrClass::ListMgrClass", this->theWho, "init");
}

ListMgrClass::~ListMgrClass (void)
{
    if (strcmp(this->objectName(), "ListMgrClass")) {
        phwangAbendWS("~ListMgrClass", this->theWho, this->objectName());
    }
    strcpy(this->theObjectName, "ListMgrClassDummy");
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
    for (int i = 0; i < LIST_MGR_ID_INDEX_ARRAY_SIZE; i++) {
        if (!this->theEntryTableArray[i]) {
            if (i > this->theMaxIndex) {
                this->theMaxIndex = i;
            }
            this->theEntryCount++;
            return i;
        }
    }

    phwangAbendWS("ListMgrClass::allocEntryIndex", this->theWho, "out of entry_index");
    return -1;
}

void ListMgrClass::insertEntry (ListEntryClass *entry_val)
{
    phwangDebugWS(false, "ListMgrClass::insertEntry", this->theWho, "");

    this->abendListMgrClass("before insertEntry");
    pthread_mutex_lock(&this->theMutex);

    entry_val->setEntryId(this->allocEntryId());
    entry_val->setEntryIndex(this->allocEntryIndex());
    if (entry_val->entryIndex() != -1) {
        phwangEncodeIdIndex(entry_val->entryIdIndex(), entry_val->entryId(), this->theIdSize, entry_val->entryIndex(), this->theIndexSize);
        this->theEntryTableArray[entry_val->entryIndex()] = entry_val;
    }
    else {
        phwangAbendWS("ListMgrClass::insertEntry", this->theWho, "TBD");
    }

    pthread_mutex_unlock(&this->theMutex);
    this->abendListMgrClass("after insertEntry");
}

void ListMgrClass::removeEntry (ListEntryClass *list_entry_object_val)
{
    this->abendListMgrClass("before removeEntry");
    pthread_mutex_lock(&this->theMutex);
    this->theEntryTableArray[list_entry_object_val->entryIndex()] = 0;
    this->theEntryCount--;
    pthread_mutex_unlock(&this->theMutex);
    this->abendListMgrClass("after removeEntry");
}

void ListMgrClass::abendListMgrClass (char const *msg_val)
{
    pthread_mutex_lock(&this->theMutex);
    int count = 0;
    for (int i = 0; i < LIST_MGR_ID_INDEX_ARRAY_SIZE; i++) {
        if (this->theEntryTableArray[i]) {
            count++;
        }
    }
    if (this->theEntryCount != count) {
        phwangAbendWS("ListMgrClass::abendListMgrClass", this->theWho, "count not match");
    }
    pthread_mutex_unlock(&this->theMutex);
}

ListEntryClass *ListMgrClass::searchEntry (char const *data_val, void *extra_data_val)
{
    int entry_id;
    int entry_index;

    phwangDebugWS(false, "ListMgrClass::searchEntry", this->theWho, data_val);

    phwangDecodeIdIndex(data_val, &entry_id, this->theIdSize, &entry_index, this->theIndexSize);

    if (0) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "entry_id=%d entry_index=%d", entry_id, entry_index);
        phwangLogitWS("ListMgrClass::searchEntry", this->theWho, s);
    }

    return this->getEntryByIdIndex(entry_id, entry_index, extra_data_val);
}

ListEntryClass *ListMgrClass::getEntryByIdIndex (int entry_id_val, int link_index_val, void *extra_data_val)
{
    if (false && this->debugOn_) {
        printf("ListMgrClass::getEntryByIdIndex(%s) id=%d index=%d\n", this->theWho, entry_id_val, link_index_val);
    }

    if (entry_id_val > LIST_MGR_MAX_GLOBAL_LIST_ID) {
        printf("ListMgrClass::getEntryByIdIndex(%s) id=%d index=%d\n", this->theWho, entry_id_val, link_index_val);
        phwangAbendWS("ListMgrClass::getEntryByIdIndex", this->theWho, "entry_id_val too big");
        return 0;
    }

    if (link_index_val >= LIST_MGR_MAX_GLOBAL_LIST_ID) {
        printf("ListMgrClass::getEntryByIdIndex(%s) id=%d index=%d\n", this->theWho, entry_id_val, link_index_val);
        phwangAbendWS("ListMgrClass::getEntryByIdIndex", this->theWho, "link_index_val too big");
        return 0;
    }

    ListEntryClass *entry = this->theEntryTableArray[link_index_val];
    if (!entry) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "null entry: entry_id_val=%d link_index_val=%d theEntryCount=%d extra_data_val=%s", entry_id_val, link_index_val, this->theEntryCount, (char *)extra_data_val);
        phwangLogitWS("ListMgrClass::getEntryByIdIndex", this->theWho, s);
        return 0;
    }

    if (entry->entryId() != entry_id_val){
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "entry id not match: entryId=%d entry_id_val=%d extra_data_val=%s", entry->entryId(), entry_id_val, (char *)extra_data_val);
        phwangAbendWS("ListMgrClass::getEntryByIdIndex", this->theWho, s);
        return 0;
    }

    return entry;
}
