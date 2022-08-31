/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_util_class.h
*/

#pragma once

#include "/usr/include/postgresql/libpq-fe.h"

class SqlClass {
    PGconn *theGoConnect;

    PGconn *connectGoDb(void);
    void createTables (void);
    void insertAccount(char const *str_val);

    void createAccountTable(void);
    void createCarTable(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);
   
public:
    SqlClass(void);
    ~SqlClass(void);

    char const *objectName(void) {return "SqlClass";}
    PGconn *goConnect(void) {return this->theGoConnect;}


    /* exports */
};
