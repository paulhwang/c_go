/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_class.cpp
*/

#include "../../phwang_dir/phwang.h"
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
    char *buf = (char *) malloc(strlen("str_val") + 1);
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

    this->sqlObject()->createTable2(this->sqlConnect(), "accounts", "name VARCHAR(20)", "password VARCHAR(20)");

    DbAccountEntryClass *entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("admin"));
    entry->setPassword(mallocConstStrBuf("adminpassword"));
    this->insertAccountEntry(entry);

    entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("phwang"));
    entry->setPassword(mallocConstStrBuf("phwangpassword"));
    this->insertAccountEntry(entry);

    entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("ikolre"));
    entry->setPassword(mallocConstStrBuf("ikolrepassword"));
    this->insertAccountEntry(entry);

    entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("guest"));
    entry->setPassword(mallocConstStrBuf("guestpassword"));
    this->insertAccountEntry(entry);

    entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("BigBrave"));
    entry->setPassword(mallocConstStrBuf("bigbrave"));
    this->insertAccountEntry(entry);

    entry = new DbAccountEntryClass();
    entry->setAccountName(mallocConstStrBuf("paul"));
    entry->setPassword(mallocConstStrBuf("paulpassword"));
    this->insertAccountEntry(entry);
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
    sprintf(buf, "%d, '%s','%s'", this->accountIndex(), entry_val->accountName(), entry_val->password());
    //printf("buf=%s", buf);

    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", buf);

    delete entry_val;
}

int DbAccountClass::checkAccountNameExist (char const *account_name_val)
{
    void *res;
    res = this->sqlObject()->selectFrom(this->sqlConnect(), "name");
    if (!res) {
        -1;
    }

    int count = this->sqlObject()->getPQntuples(res);
    for (int i = 0; i < count; i++) {
        char *account_name = this->sqlObject()->getTuplesValue(res, i, 0);
 
        this->debug(false, "checkAccountNameExist", account_name);

        if (!strcmp(account_name, account_name_val)) {
            this->sqlObject()->doPQclear(res);
            this->debug(true, "checkAccountNameExist", "found");
            return 0;
        }
    }

    this->sqlObject()->doPQclear(res);
    this->debug(true, "checkAccountNameExist", "not found");
    return -2;
}

int DbAccountClass::checkPassword (char const *account_name_val, char const *password_val)
{
    void *res;
    res = this->sqlObject()->selectFrom(this->sqlConnect(), "name, password");
    if (!res) {
        -1;
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
                return 0;
            }
            else {
                this->sqlObject()->doPQclear(res);
                this->debug(true, "checkPassword", "not match");
                return -1;
            }
        }
    }

    this->sqlObject()->doPQclear(res);
    this->debug(true, "checkPassword", "not found");
    return -2;
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
