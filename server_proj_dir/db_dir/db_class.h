/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_class.h
*/

#pragma once

class SqlClass;
class DbAccountClass;
class DbTestClass;
class FabricClass;

class DbClass {
    SqlClass *theSqlObject;
    DbAccountClass *theDbAccountObject;
    DbTestClass *theDbTestObject;
    void *theSqlConnect;

    DbTestClass *dbTestObject(void) {return this->theDbTestObject;}
   
public:
    DbClass(FabricClass *fabric_object_val);
    ~DbClass(void);

    SqlClass *sqlObject(void) {return this->theSqlObject;}
    void *sqlConnect(void) {return this->theSqlConnect;}
    DbAccountClass *dbAccountObject(void) {return this->theDbAccountObject;}
    char const *objectName(void) {return "DbClass";}
};
