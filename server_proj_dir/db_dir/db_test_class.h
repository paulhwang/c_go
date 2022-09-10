/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_test_class.h
*/

#pragma once

class SqlClass;
class DbClass;

class DbTestClass {
    DbClass *theDbObject;

    DbClass *dbObject() {return this->theDbObject;}
    SqlClass *sqlObject(void);
    void *sqlConnect(void);

    int createCarTable(void);
    void insertCar(void);
   
public:
    DbTestClass(DbClass *db_object_val);
    ~DbTestClass(void);

    char const *objectName(void) {return "DbTestClass";}

    void testDb(void);
};
