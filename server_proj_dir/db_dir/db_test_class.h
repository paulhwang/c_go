/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_test_class.h
*/

#pragma once

class SqlClass;

class DbTestClass {
    SqlClass *theSqlObject;
    void *theSqlConnect;

    SqlClass *sqlObject(void) {return this->theSqlObject;}
    void *sqlConnect(void) {return this->theSqlConnect;}

    int initDb(void);
    void testDb(void);
    void *connectGoDb(void);
    void createTables (void);
    void insertAccount(void);
    void insertCar(void);

    int createAccountTable(void);
    int createCarTable(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);
   
public:
    DbTestClass(void);
    ~DbTestClass(void);

    char const *objectName(void) {return "DbTestClass";}
};
