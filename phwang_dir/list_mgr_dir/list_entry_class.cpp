/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "list_entry_class.h"
#include "list_mgr_class.h"

/*
ListEntryClass::ListEntryClass (ListMgrClass *list_mgr_object, int entry_id_val, int entry_index_val, void *data_val, int id_size_val, int index_size_val):
        theEntryId(entry_id_val),
        theEntryIndex(entry_index_val),
        theEntryData(data_val),
        theIdSize(id_size_val),
        theIndexSize(index_size_val)
{
    //memset(this, 0, sizeof(ListEntryClass));
    this->theListMgrObject = list_mgr_object;
    this->theEntryIdIndex = (char *) malloc(this->theIdSize + this->theIndexSize + 4);
    phwangEncodeIdIndex(this->theEntryIdIndex, this->theEntryId, this->theIdSize, this->theEntryIndex, this->theIndexSize);

    this->debug(true, "ListEntryClass", this->theEntryIdIndex);
}
*/

ListEntryClass::ListEntryClass (ListMgrClass *list_mgr_object, int id_size_val, int index_size_val):
        theListMgrObject(list_mgr_object),
        theEntryId(0),
        theEntryIndex(0),
        theIdSize(id_size_val),
        theIndexSize(index_size_val)
{
    //memset(this, 0, sizeof(ListEntryClass));
    this->theEntryIdIndex = (char *) malloc(this->theIdSize + this->theIndexSize + 4);
    this->theListMgrObject->insertEntry(this);
    phwangEncodeIdIndex(this->theEntryIdIndex, this->theEntryId, this->theIdSize, this->theEntryIndex, this->theIndexSize);

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
