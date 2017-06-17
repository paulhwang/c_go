/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "list_entry_class.h"

ListEntryClass::ListEntryClass (ListMgrClass *list_mgr_object, int entry_id_val)
{
    memset(this, 0, sizeof(ListEntryClass));
    this->theListMgrObject = list_mgr_object;
    this->theEntryId = entry_id_val;

    if (1) {
        this->logit("ListEntryClass", "init");
    }

}

ListEntryClass::~ListEntryClass (void)
{

}

void ListEntryClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void ListEntryClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
