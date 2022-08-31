/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_test_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/sql_dir/sql_class.h"
#include "db_test_class.h"
#include "db_class.h"

SqlClass *DbTestClass::sqlObject(void) {return this->dbObject()->sqlObject();}
void *DbTestClass::sqlConnect(void) {return this->dbObject()->sqlConnect();}

DbTestClass::DbTestClass (DbClass *db_object_val)
{
    memset(this, 0, sizeof(*this));
    this->debug(false, "DbTestClass", "init");

    this->theDbObject = db_object_val;

    this->testDb();
}

DbTestClass::~DbTestClass (void)
{
}

void DbTestClass::testDb(void)
{
    this->createTables();
    this->insertAccount();
    this->insertCar();
}

void DbTestClass::createTables (void) {
    this->createAccountTable();
    this->createCarTable();
}

int DbTestClass::createAccountTable (void)
{
    int result = this->sqlObject()->dropTableIfExist(this->sqlConnect(), "accounts");
    if (result == -1) {
        return result;
    }

    return this->sqlObject()->createTable2(this->sqlConnect(), "accounts", "name VARCHAR(20)", "password VARCHAR(20)");
}


void DbTestClass::insertAccount (void) {
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "1, 'admin','p001'");
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "2, 'phwang','p002'");
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "3, 'paul','p003'");

    void *res;
    res = this->sqlObject()->selectFrom(this->sqlConnect());
    if (!res) {
        return;
    }

    int i = 0;
    while (1) {
        char *data = this->sqlObject()->getTuplesValue(res, i , 0);
        if (!data)
            break;
        printf("data=%s\n", data);
        i++;
    }

    this->sqlObject()->pQclear(res);
}

int DbTestClass::createCarTable (void) {
    int result = this->sqlObject()->dropTableIfExist(this->sqlConnect(), "cars");
    if (result == -1) {
        return result;
    }

    return this->sqlObject()->createTable2(this->sqlConnect(), "cars", "name VARCHAR(20)", "price INT");
}

void DbTestClass::insertCar (void) {
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "1,'Audi',52642");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "2,'Mercedes',57127");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "3,'Skoda',9000");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "4,'Volvo',29000");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "5,'Bentley',350000");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "6,'Citroen',21000");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "7,'Hummer',41400");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "8,'Volkswagen',21600");
}

void DbTestClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DbTestClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
