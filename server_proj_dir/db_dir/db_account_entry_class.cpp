/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_entry_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "db_account_entry_class.h"

std::atomic<int> DbAccountEntryClass::ObjectCount(0);

DbAccountEntryClass::DbAccountEntryClass (void)
{
    memset(this, 0, sizeof(*this));
    phwangIncrementAtomicCount(&ObjectCount, this->objectName(), 3);
}

DbAccountEntryClass::~DbAccountEntryClass (void)
{
    phwangDecrementAtomicCount(&ObjectCount, this->objectName());

    if (this->theAccountName) {
        phwangFree(this->theAccountName);
    }
    if (this->thePassword) {
        phwangFree(this->thePassword);
    }
    if (this->theEmail) {
        phwangFree(this->theEmail);
    }
}
