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
    this->debug(false, "DbAccountClass", "init");

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

char *mallocConstStrBuf (char const * str_val)
{
    char *buf = (char *) phwangMalloc1(strlen(str_val) + 1, MallocClass::DB_ACCOUNT_DEFAULT_NAME);
    strcpy(buf, str_val);
    return buf;
}

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

    DbAccountEntryClass *entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("admin"));
    entry->setPassword(mallocConstStrBuf("admin_password"));
    entry->setEmail(mallocConstStrBuf("admin@phwang.com"));
    this->insertAccountEntry(entry);

    entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("phwang"));
    entry->setPassword(mallocConstStrBuf("a"));
    entry->setEmail(mallocConstStrBuf("phwang@phwang.com"));
    this->insertAccountEntry(entry);

    entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("ikolre"));
    entry->setPassword(mallocConstStrBuf("ikolre_password"));
    entry->setEmail(mallocConstStrBuf("ikolre@phwang.com"));
    this->insertAccountEntry(entry);

    entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("guest"));
    entry->setPassword(mallocConstStrBuf("guest_password"));
    entry->setEmail(mallocConstStrBuf("guest@phwang.com"));
    this->insertAccountEntry(entry);

    entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("BigBrave"));
    entry->setPassword(mallocConstStrBuf("bigbrave"));
    entry->setEmail(mallocConstStrBuf("bigbrave@phwang.com"));
    this->insertAccountEntry(entry);

    entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("paul"));
    entry->setPassword(mallocConstStrBuf("a"));
    entry->setEmail(mallocConstStrBuf("paul@phwang.com"));
    this->insertAccountEntry(entry);

    /****** the buf malloc by mallocConstStrBuf has been free by the insertAccountEntry ********/
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

        if (1) { //debug
            char buf[256];
            sprintf(buf, "account_name=%s, password=%s", account_name, password);
            this->logit("listAccount", buf);
        }
    }

    this->sqlObject()->doPQclear(res);
}

void DbAccountClass::insertAccountEntry(DbAccountEntryClass *entry_val)
{
    char buf[516];
    this->incrementAccountIndex();
    sprintf(buf, "%d, '%s','%s','%s'", this->accountIndex(), entry_val->accountName(), entry_val->password(), entry_val->email());
    //printf("buf=%s", buf);

    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", buf);

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
 
        this->debug(false, "checkAccountNameExist", account_name);

        if (!strcmp(account_name, account_name_val)) {
            this->sqlObject()->doPQclear(res);
            this->debug(true, "checkAccountNameExist", "found");
            return DB_ACCOUNT_NAME_EXIST;
        }
    }

    this->sqlObject()->doPQclear(res);
    this->debug(true, "checkAccountNameExist", "not found");
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

        if (0) { //debug
            char buf[256];
            sprintf(buf, "account_name=%s, password=%s", account_name, password);
            this->logit("checkPassword", buf);
        }

        if (!strcmp(account_name, account_name_val)) {
            if (!strcmp(password, password_val)) {
                this->sqlObject()->doPQclear(res);
                this->debug(true, "checkPassword", "match");
                return DB_ACCOUNT_PASSWORD_MATCH;
            }
            else {
                this->sqlObject()->doPQclear(res);
                this->debug(true, "checkPassword", "not match");
                return DB_ACCOUNT_PASSWORD_NOT_MATCH;
            }
        }
    }

    this->sqlObject()->doPQclear(res);
    this->debug(true, "checkPassword", "not found");
    return DB_ACCOUNT_NAME_NOT_EXIST;
}

void DbAccountClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DbAccountClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
