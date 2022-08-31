/*
  Copyrights reserved
  Written by Paul Hwang
  File name: sql_class.h
*/

#pragma once

#include "/usr/include/postgresql/libpq-fe.h"

class SqlClass {
    void errPQexec(PGconn *conn_val, PGresult *res_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);
   
public:
    SqlClass(void);
    ~SqlClass(void);

    char const *objectName(void) {return "SqlClass";}

    /* exports */
    PGconn *connectDb(char const *user_val, char const *dbname_val);
    void disconnectDb (void *conn_val);
    int createTable2(void *conn_val, char const *table_name_val, char const *val1, char const *val2);
    int dropTableIfExist(void *conn_val, char const *table_name_val);
    void insertAccount (void *conn_val, char const *table_val, char const *values_val);
    PGresult *selectFrom (void *conn_val);
    char *getTuplesValue(PGresult *res_val, int row_number_val, int column_number_val);
    void pQclear(PGresult *res_val);
};
