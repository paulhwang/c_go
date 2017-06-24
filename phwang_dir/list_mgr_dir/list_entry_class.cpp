/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "list_entry_class.h"
#include "list_mgr_class.h"

ListEntryClass::ListEntryClass (ListMgrClass *list_mgr_object):
        theListMgrObject(list_mgr_object),
        theEntryId(0),
        theEntryIndex(0)
{
    //memset(this, 0, sizeof(ListEntryClass));
    this->theEntryIdIndex = (char *) malloc(this->theListMgrObject->theIdSize + this->theListMgrObject->theIndexSize + 4);
    this->theListMgrObject->insertEntry(this);
    phwangEncodeIdIndex(this->theEntryIdIndex, this->theEntryId, this->theListMgrObject->theIdSize, this->theEntryIndex, this->theListMgrObject->theIndexSize);

    this->debug(true, "ListEntryClass", this->theEntryIdIndex);
}

ListEntryClass::~ListEntryClass (void)
{
    free(this->theEntryIdIndex);
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
