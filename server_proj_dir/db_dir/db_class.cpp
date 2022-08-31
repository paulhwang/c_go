/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/sql_dir/sql_class.h"
#include "db_class.h"
#include "db_test_class.h"

DbClass::DbClass (void)
{
    memset(this, 0, sizeof(*this));
    this->debug(false, "DbClass", "init");

    this->theSqlObject = new SqlClass();
    if (this->initDb() == -1) {
        //tbd
    }

    this->testDb();
}

DbClass::~DbClass (void)
{
}

int DbClass::initDb(void)
{
    this->theSqlConnect = this->connectGoDb();
    if (this->sqlConnect() == 0) {
        this->abend("DbClass", "fail to connnect to go_db");
        return -1;
    }
    return 0;
}

void *DbClass::connectGoDb (void)
{
    return this->sqlObject()->connectDb("phwang", "go_db");
}

void DbClass::testDb(void)
{
    this->theDbTestObject = new DbTestClass(this);
    this->dbTestObject()->testDb();
}

void DbClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DbClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
