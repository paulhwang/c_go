/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_util_class.h
*/

#pragma once

#include "/usr/include/postgresql/libpq-fe.h"

class SqlClass {
    PGconn *theGoConnect;


    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);
   
public:
    SqlClass(void);
    ~SqlClass(void);

    char const *objectName(void) {return "SqlClass";}

    PGconn *goConnect(void) {return this->theGoConnect;}
    PGconn *connectGoDb(void);
    void createTables (PGconn *conn_val);
    void insertAccount(PGconn *conn_val);

    void createAccountTable(PGconn *conn_val);
    void createCarTable(PGconn *conn_val);


    /* exports */
    PGconn *connectDb(char const *user_val, char const *dbname_val);
};
