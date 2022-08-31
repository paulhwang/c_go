/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/sql_dir/sql_class.h"
#include "db_class.h"

DbClass::DbClass (void)
{
    memset(this, 0, sizeof(*this));
    this->debug(true, "DbClass", "init");

    this->theSqlObject = new SqlClass();

    this->theGoConnect = this->connectGoDb();
    if (this->goConnect() == 0) {
        this->abend("connectDbs", "fail to connnect to go_db");
        return;
    }

    this->sqlObject()->createTables(this->theGoConnect);
    this->sqlObject()->insertAccount(this->theGoConnect);

}

DbClass::~DbClass (void)
{
}

PGconn *DbClass::connectGoDb (void)
{
    return this->sqlObject()->connectDb("phwang", "go_db");
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
