/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/sql_dir/sql_class.h"
#include "db_class.h"
#include "db_account_class.h"
#include "db_test_class.h"

DbClass::DbClass (void)
{
    memset(this, 0, sizeof(*this));
    this->debug(false, "DbClass", "init");

    /* sql */
    this->theSqlObject = new SqlClass();

    /* connect */
    this->theSqlConnect = this->sqlObject()->connectDb("phwang", "go_db");
    if (this->sqlConnect() == 0) {
        this->abend("DbClass", "fail to connnect to go_db");
        return;
    }

    /* account */
    this->theDbAccountObject = new DbAccountClass(this);

    /* test */
    this->theDbTestObject = new DbTestClass(this);
    this->dbTestObject()->testDb();
}

DbClass::~DbClass (void)
{
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
