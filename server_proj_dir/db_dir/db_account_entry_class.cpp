/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_entry_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "db_account_entry_class.h"

int DbAccountEntryClass::ObjectCount = 0;

DbAccountEntryClass::DbAccountEntryClass (void)
{
    memset(this, 0, sizeof(*this));
    phwangIncrementObjectCount(&ObjectCount, this->objectName(), 3);
}

DbAccountEntryClass::~DbAccountEntryClass (void)
{
    phwangDecrementObjectCount(&ObjectCount);

    if (this->theAccountName) {
        phwangFree(this->theAccountName, 0);
    }
    if (this->thePassword) {
        phwangFree(this->thePassword, 0);
    }
    if (this->theEmail) {
        phwangFree(this->theEmail, 0);
    }
}

void DbAccountEntryClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DbAccountEntryClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
