/*
  Copyrights reserved
  Written by Paul Hwang
  File name: list_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "list_entry_class.h"
#include "list_mgr_class.h"

ListEntryClass::ListEntryClass (void *list_mgr_object)
{
    memset(this, 0, sizeof(*this));
    this->theListMgrObject = (ListMgrClass *) list_mgr_object;
    this->theEntryId = 0;
    this->theEntryIndex = 0;

    if (this->theListMgrObject->idSize() + this->theListMgrObject->indexSize() > LIST_ENTRY_CLASS_ID_INDEX_BUFFER_SIZE) {
        phwangAbendS("ListEntryClass::ListEntryClass", "buffer too small");
    }

    this->theListMgrObject->insertEntry(this);
    phwangEncodeIdIndex(this->theEntryIdIndex, this->theEntryId, this->theListMgrObject->idSize(), this->theEntryIndex, this->theListMgrObject->indexSize());

    phwangDebugS(false, "ListEntryClass::ListEntryClass", this->theEntryIdIndex);
}

ListEntryClass::~ListEntryClass (void)
{
    this->theListMgrObject->removeEntry(this);
}
