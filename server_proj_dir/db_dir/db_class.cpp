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

DbClass::DbClass (FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(*this));
    phwangDebugS(false, "DbClass::DbClass", "init");

    /* sql */
    this->theSqlObject = new SqlClass();

    /* connect */
    this->theSqlConnect = this->sqlObject()->connectDb("phwang", "go_db");
    if (this->sqlConnect() == 0) {
        phwangAbendS("DbClass::DbClass", "fail to connnect to go_db");
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
