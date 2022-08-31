/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_class.h
*/

#pragma once

class SqlClass;

#include "/usr/include/postgresql/libpq-fe.h"

class DbClass {
    SqlClass *theSqlObject;
    PGconn *theSqlConnect;

    SqlClass *sqlObject(void) {return this->theSqlObject;}
    PGconn *sqlConnect(void) {return this->theSqlConnect;}

    PGconn *connectGoDb(void);
    void createTables (void);
    void insertAccount(void);
    void insertCar(void);

    int createAccountTable(void);
    int createCarTable(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);
   
public:
    DbClass(void);
    ~DbClass(void);

    char const *objectName(void) {return "DbClass";}
};
