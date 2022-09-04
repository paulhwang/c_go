/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_entry_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "db_account_entry_class.h"

DbAccountEntryClass::DbAccountEntryClass (void)
{
    memset(this, 0, sizeof(*this));
    this->incrementObjectCount();
}

DbAccountEntryClass::~DbAccountEntryClass (void)
{
    if (this->theAccountName) {
        free(this->theAccountName);
    }
    if (this->thePassword) {
        free(this->thePassword);
    }
    if (this->theEmail) {
        free(this->theEmail);
    }

    this->decrementObjectCount();

}

void DbAccountEntryClass::incrementObjectCount(void)
{
    DbAccountEntryClass::theObjectCount++;
    if (DbAccountEntryClass::theObjectCount > 5) {
        this->abend("incrementObjectCount", "too big");
    }
}

void DbAccountEntryClass::decrementObjectCount(void)
{
    DbAccountEntryClass::theObjectCount--;
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
