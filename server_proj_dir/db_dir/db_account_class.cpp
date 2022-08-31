/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/sql_dir/sql_class.h"
#include "db_class.h"
#include "db_account_class.h"

DbAccountClass::DbAccountClass (void)
{
    memset(this, 0, sizeof(*this));
    this->debug(false, "DbAccountClass", "init");

    this->theSqlObject = new SqlClass();
    if (this->initDb() == -1) {
        //tbd
    }

    this->initAccount();
    this->listAccount();
}

DbAccountClass::~DbAccountClass (void)
{
}

int DbAccountClass::initDb(void)
{
    this->theSqlConnect = this->connectGoDb();
    if (this->sqlConnect() == 0) {
        this->abend("DbClass", "fail to connnect to go_db");
        return -1;
    }
    return 0;
}

void *DbAccountClass::connectGoDb (void)
{
    return this->sqlObject()->connectDb("phwang", "go_db");
}

int db_account_class_do_init_account = 0;

void DbAccountClass::initAccount(void)
{
    if (!db_account_class_do_init_account) {
        return;
    }

    int result = this->sqlObject()->dropTableIfExist(this->sqlConnect(), "accounts");
    if (result == -1) {
        return;
    }

    this->sqlObject()->createTable2(this->sqlConnect(), "accounts", "name VARCHAR(20)", "password VARCHAR(20)");

    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "1, 'admin','admin'");
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "2, 'phwang','phwang'");
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "3, 'ikolre','ikolre'");
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "4, 'guest','a'");
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "5, 'BigBrave','bigbrave'");
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "6, 'paul','paul'");
}

void DbAccountClass::listAccount (void) {
    void *res;
    res = this->sqlObject()->selectFrom(this->sqlConnect());
    if (!res) {
        return;
    }

    int count = this->sqlObject()->getPQntuples(res);
    for (int i = 0; i < count; i++) {
        char *data = this->sqlObject()->getTuplesValue(res, i, 0);
        this->debug(true, "listAccount", data);
    }

    this->sqlObject()->doPQclear(res);
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
