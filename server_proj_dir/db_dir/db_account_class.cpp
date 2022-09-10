/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../phwang_dir/sql_dir/sql_class.h"
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
    this->listAccount();
    this->checkAccountNameExist("phwang");
    this->checkAccountNameExist("phwangaaa");
    this->checkPassword("phwang", "phwang");
    this->checkPassword("phwang", "phwangpassword");
}

/************************DO NOT MODIFY IT*******************/
int db_account_class_do_create_account_table_in_database = 1;
/************************DO NOT MODIFY IT*******************/

void DbAccountClass::createAccountTableInDatabase(void)
{
    if (!db_account_class_do_create_account_table_in_database) {
        return;
    }

    int result = this->sqlObject()->dropTableIfExist(this->sqlConnect(), "accounts");
    if (result == -1) {
        return;
    }

    this->sqlObject()->createTable3(this->sqlConnect(), "accounts", "name VARCHAR(20)", "password VARCHAR(20)", "email VARCHAR(30)");

    this->createAccount("admin", "admin_password", "admin@phwang.com");
    this->createAccount("phwang", "a", "phwang@phwang.com");
    this->createAccount("ikolre", "ikolre_password", "ikolre@phwang.com");
    this->createAccount("guest", "guest_password", "guest@phwang.com");
    this->createAccount("BigBrave", "a", "bigbrave@phwang.com");
    this->createAccount("paul", "a", "paul@phwang.com");
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

int DbAccountClass::checkAccountNameExist (char const *account_name_val)
{
    void *res;
    res = this->sqlObject()->selectFrom(this->sqlConnect(), "name");
    if (!res) {
        DB_ACCOUNT_SELECT_FAIL;
    }

    int count = this->sqlObject()->getPQntuples(res);
    for (int i = 0; i < count; i++) {
        char *account_name = this->sqlObject()->getTuplesValue(res, i, 0);
 
        phwangDebugS(false, "DbAccountClass::checkAccountNameExist", account_name);

        if (!strcmp(account_name, account_name_val)) {
            this->sqlObject()->doPQclear(res);
            phwangDebugS(false, "DbAccountClass::checkAccountNameExist", "found");
            return DB_ACCOUNT_NAME_EXIST;
        }
    }

    this->sqlObject()->doPQclear(res);
    phwangDebugS(false, "DbAccountClass::checkAccountNameExist", "not found");
    return DB_ACCOUNT_NAME_NOT_EXIST;
}

int DbAccountClass::checkPassword (char const *account_name_val, char const *password_val)
{
    void *res;
    res = this->sqlObject()->selectFrom(this->sqlConnect(), "name, password");
    if (!res) {
        DB_ACCOUNT_SELECT_FAIL;
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
                return DB_ACCOUNT_PASSWORD_MATCH;
            }
            else {
                this->sqlObject()->doPQclear(res);
                phwangDebugS(false, "DbAccountClass::checkPassword", "not match");
                return DB_ACCOUNT_PASSWORD_NOT_MATCH;
            }
        }
    }

    this->sqlObject()->doPQclear(res);
    phwangDebugS(false, "DbAccountClass::checkPassword", "not found");
    return DB_ACCOUNT_NAME_NOT_EXIST;
}
