/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_root_class.cpp
*/

#include "../phwang.h"
#include "list_mgr_root_class.h"
#include "list_mgr_class.h"

ListMgrRootClass::ListMgrRootClass (int debug_code_val)
{
    memset(this, 0, sizeof (*this));
}

ListMgrRootClass::~ListMgrRootClass(void)
{
}

void *ListMgrRootClass::listMgrMalloc (char const *caller_name_val, int id_size_val, int index_size_val, int global_entry_id_val)
{
    ListMgrClass *list_mgr = new ListMgrClass(caller_name_val, id_size_val, index_size_val, global_entry_id_val);
    return list_mgr;
}

void ListMgrRootClass::listMgrFree (void *list_mgr_val)
{
    if (!list_mgr_val) {
        this->abend("listMgrFree", "null list_mgr_val");
        return;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        this->abend("listMgrFree", s);
        return;
    }

    ((ListMgrClass *) list_mgr_val)->~ListMgrClass();
}

void ListMgrRootClass::listMgrRemoveEntry (void *list_mgr_val, void *entry_val)
{
    if (!list_mgr_val) {
        this->abend("listMgrRemoveEntry", "null list_mgr_val");
        return;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        this->abend("listMgrRemoveEntry", s);
        return;
    }

    ((ListMgrClass *) list_mgr_val)->removeEntry((ListEntryClass *) entry_val);
}

void *ListMgrRootClass::listMgrSearchEntry(void *list_mgr_val, char const *data_val, void *extra_data_val)
{
    if (!list_mgr_val) {
        this->abend("listMgrSearchEntry", "null list_mgr_val");
        return 0;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        this->abend("listMgrSearchEntry", s);
        return 0;
    }

    return ((ListMgrClass *) list_mgr_val)->searchEntry(data_val, extra_data_val);
}

int ListMgrRootClass::listMgrGetMaxIndex (void *list_mgr_val, char const *who_val)
{
    if (!list_mgr_val) {
        this->abend("listMgrGetMaxIndex", "null list_mgr_val");
        return 0;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: who=%s objectName=%s", who_val, ((ListMgrClass *) list_mgr_val)->objectName());
        this->abend("listMgrGetMaxIndex", s);
        return 0;
    }

    return ((ListMgrClass *) list_mgr_val)->maxIndex();
}

void *ListMgrRootClass::listMgrGetEntryTableArray (void *list_mgr_val)
{
    if (!list_mgr_val) {
        this->abend("listMgrGetEntryTableArray", "null list_mgr_val");
        return 0;
    }

    if (strcmp(((ListMgrClass *) list_mgr_val)->objectName(), "ListMgrClass")) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "wrong object: objectName=%s", ((ListMgrClass *) list_mgr_val)->objectName());
        this->abend("listMgrGetEntryTableArray", s);
        return 0;
    }

    return ((ListMgrClass *) list_mgr_val)->entryTableArray();
}

void ListMgrRootClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ListMgrRootClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
