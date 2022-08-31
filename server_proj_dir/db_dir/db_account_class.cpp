/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/sql_dir/sql_class.h"
#include "db_class.h"
#include "db_account_class.h"

SqlClass *DbAccountClass::sqlObject(void) {return this->dbObject()->sqlObject();}
void *DbAccountClass::sqlConnect(void) {return this->dbObject()->sqlConnect();}

DbAccountClass::DbAccountClass (DbClass *db_object_val)
{
    memset(this, 0, sizeof(*this));
    this->debug(false, "DbAccountClass", "init");

    this->theDbObject = db_object_val;

    this->createAccountTableInDatabase();

    this->listAccount();
    this->developTest();
}

DbAccountClass::~DbAccountClass (void)
{
}

void DbAccountClass::developTest(void)
{
}

/************************DO NOT MODIFY IT*******************/
int db_account_class_do_create_account_table_in_database = 0;
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
    res = this->sqlObject()->selectFrom(this->sqlConnect(), "name, password");
    if (!res) {
        return;
    }

    int count = this->sqlObject()->getPQntuples(res);
    for (int i = 0; i < count; i++) {
        char *data1 = this->sqlObject()->getTuplesValue(res, i, 0);
        this->debug(true, "listAccount", data1);
        char *data2 = this->sqlObject()->getTuplesValue(res, i, 1);
        this->debug(true, "listAccount", data2);
    }

    this->sqlObject()->doPQclear(res);
}

int DbAccountClass::checkPassword (char const *account_name_val, char const *password_val)
{
    return 0;
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
