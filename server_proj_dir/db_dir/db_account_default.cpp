/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_default.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/malloc_dir/malloc_class.h"
#include "../../phwang_dir/sql_dir/sql_class.h"
#include "db_class.h"
#include "db_account_class.h"
#include "db_account_entry_class.h"

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
    this->createAccount("phwang", "phwang_password", "phwang@phwang.com");
    this->createAccount("ikolre", "ikolre_password", "ikolre@phwang.com");
    this->createAccount("guest", "guest_password", "guest@phwang.com");
    this->createAccount("BigBrave", "bigbrave_password", "bigbrave@phwang.com");
    this->createAccount("paul", "paul_password", "paul@phwang.com");
    this->createAccount("a", "", "a@phwang.com");
    this->createAccount("b", "", "a@phwang.com");
    this->createAccount("c", "", "a@phwang.com");
}
