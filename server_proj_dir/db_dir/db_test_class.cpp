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
    phwangDebugS(false, "DbTestClass::DbTestClass", "init");

    this->theDbObject = db_object_val;
}

DbTestClass::~DbTestClass (void)
{
}

void DbTestClass::testDb(void)
{
    this->createCarTable();
    this->insertCar();
}

int DbTestClass::createCarTable (void) {
    int result = this->sqlObject()->dropTableIfExist(this->sqlConnect(), "cars");
    if (result == -1) {
        return result;
    }

    return this->sqlObject()->createTable2(this->sqlConnect(), "cars", "name VARCHAR(20)", "price INT");
}

void DbTestClass::insertCar (void) {
    this->sqlObject()->insertInto (this->sqlConnect(), "cars", "1,'Audi',52642");
    this->sqlObject()->insertInto (this->sqlConnect(), "cars", "2,'Mercedes',57127");
    this->sqlObject()->insertInto (this->sqlConnect(), "cars", "3,'Skoda',9000");
    this->sqlObject()->insertInto (this->sqlConnect(), "cars", "4,'Volvo',29000");
    this->sqlObject()->insertInto (this->sqlConnect(), "cars", "5,'Bentley',350000");
    this->sqlObject()->insertInto (this->sqlConnect(), "cars", "6,'Citroen',21000");
    this->sqlObject()->insertInto (this->sqlConnect(), "cars", "7,'Hummer',41400");
    this->sqlObject()->insertInto (this->sqlConnect(), "cars", "8,'Volkswagen',21600");
}
