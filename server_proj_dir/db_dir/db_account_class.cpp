/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../phwang_dir/sql_dir/sql_class.h"
#include "../define_dir/result_def.h"
#include "db_class.h"
#include "db_account_class.h"
#include "db_account_entry_class.h"

SqlClass *DbAccountClass::sqlObject(void) {return this->dbObject()->sqlObject();}
void *DbAccountClass::sqlConnect(void) {return this->dbObject()->sqlConnect();}

DbAccountClass::DbAccountClass (DbClass *db_object_val)
{
    memset(this, 0, sizeof(*this));
    phwangDebugS(false, "DbAccountClass::DbAccountClass", "init");

    this->theDbObject = db_object_val;

    this->createAccountTableInDatabase();

    this->developTest();
}

DbAccountClass::~DbAccountClass (void)
{
}

void DbAccountClass::developTest(void)
{
    char result_buf[RESULT_DEF::RESULT_SIZE + 1];

    this->listAccount();
    this->checkAccountNameExist("phwang", result_buf);
    this->checkAccountNameExist("phwangaaa", result_buf);
    this->checkPassword("phwang", "phwang", result_buf);
    this->checkPassword("phwang", "phwangpassword", result_buf);
}

void DbAccountClass::createAccount(char const *name_val, char const *psword_val, char const *email_val)
{
    DbAccountEntryClass *entry = new DbAccountEntryClass();
    entry->setAccountName(phwangMallocConstStrBuf(name_val));
    entry->setPassword(phwangMallocConstStrBuf(psword_val));
    entry->setEmail(phwangMallocConstStrBuf(email_val));
    this->insertAccountEntry(entry);
    /****** the buf malloc by phwangMallocConstStrBuf has been free by the insertAccountEntry ********/
}

void DbAccountClass::listAccount (void) {
    void *res;
    res = this->sqlObject()->selectFrom(this->sqlConnect(), "name, password");
    if (!res) {
        return;
    }

    int count = this->sqlObject()->getPQntuples(res);
    for (int i = 0; i < count; i++) {
        char *account_name = this->sqlObject()->getTuplesValue(res, i, 0);
        char *password = this->sqlObject()->getTuplesValue(res, i, 1);
        phwangDebugSS(false, "DbAccountClass::listAccount", account_name, password);
    }

    this->sqlObject()->doPQclear(res);
}

void DbAccountClass::insertAccountEntry(DbAccountEntryClass *entry_val)
{
    char buf[516];
    this->incrementAccountIndex();
    sprintf(buf, "%d, '%s','%s','%s'", this->accountIndex(), entry_val->accountName(), entry_val->password(), entry_val->email());
    //printf("buf=%s", buf);

    this->sqlObject()->insertInto (this->sqlConnect(), "accounts", buf);

    delete entry_val;
}

void DbAccountClass::checkAccountNameExist (char const *account_name_val, char *result_ptr)
{
    void *res;
    res = this->sqlObject()->selectFrom(this->sqlConnect(), "name");
    if (!res) {
        strcpy(result_ptr, RESULT_DEF::RESULT_DB_SELECT_FAIL);
        return;
    }

    int count = this->sqlObject()->getPQntuples(res);
    for (int i = 0; i < count; i++) {
        char *account_name = this->sqlObject()->getTuplesValue(res, i, 0);
 
        phwangDebugS(false, "DbAccountClass::checkAccountNameExist", account_name);

        if (!strcmp(account_name, account_name_val)) {
            this->sqlObject()->doPQclear(res);
            phwangDebugS(false, "DbAccountClass::checkAccountNameExist", "found");
            strcpy(result_ptr, RESULT_DEF::RESULT_ACCOUNT_NAME_ALREADY_EXIST);
            return;
        }
    }

    this->sqlObject()->doPQclear(res);
    phwangDebugS(false, "DbAccountClass::checkAccountNameExist", "not found");
    strcpy(result_ptr, RESULT_DEF::RESULT_ACCOUNT_NAME_NOT_EXIST);
    return;
}

void DbAccountClass::checkPassword (
    char const *account_name_val,
    char const *password_val,
    char *result_ptr)
{
    void *res;
    res = this->sqlObject()->selectFrom(this->sqlConnect(), "name, password");
    if (!res) {
        strcpy(result_ptr, RESULT_DEF::RESULT_DB_SELECT_FAIL);
        return;
    }

    int count = this->sqlObject()->getPQntuples(res);
    for (int i = 0; i < count; i++) {
        char *account_name = this->sqlObject()->getTuplesValue(res, i, 0);
        char *password = this->sqlObject()->getTuplesValue(res, i, 1);

        phwangDebugSS(false, "DbAccountClass::checkPassword", account_name, password);

        if (!strcmp(account_name, account_name_val)) {
            if (!strcmp(password, password_val)) {
                this->sqlObject()->doPQclear(res);
                phwangDebugS(false, "DbAccountClass::checkPassword", "match");
                strcpy(result_ptr, RESULT_DEF::RESULT_PASSWORD_MATCH);
                return;
            }
            else {
                this->sqlObject()->doPQclear(res);
                phwangDebugS(false, "DbAccountClass::checkPassword", "not match");
                strcpy(result_ptr, RESULT_DEF::RESULT_PASSWORD_NOT_MATCH);
                return;
            }
        }
    }

    this->sqlObject()->doPQclear(res);
    phwangDebugS(false, "DbAccountClass::checkPassword", "not found");
    strcpy(result_ptr, RESULT_DEF::RESULT_ACCOUNT_NAME_NOT_EXIST);
    return;
}
