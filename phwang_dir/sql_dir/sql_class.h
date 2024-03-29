/*
  Copyrights reserved
  Written by Paul Hwang
  File name: sql_class.h
*/

#pragma once

#include "/usr/include/postgresql/libpq-fe.h"

class SqlClass {
    void errPQexec(PGconn *conn_val, PGresult *res_val);
   
public:
    SqlClass(void);
    ~SqlClass(void);

    char const *objectName(void) {return "SqlClass";}

    /* exports */
    PGconn *connectDb(char const *user_val, char const *dbname_val);
    void disconnectDb (void *conn_val);
    int createTable(void *conn_val, char const *table_name_val, char const *data_val);
    int createTable2(void *conn_val, char const *table_name_val, char const *val1, char const *val2);
    int createTable3(void *conn_val, char const *table_name_val, char const *val1, char const *val2, char const *val3);
    int dropTableIfExist(void *conn_val, char const *table_name_val);
    void insertInto (void *conn_val, char const *table_val, char const *values_val);
    PGresult *selectFrom (void *conn_val, char const *column_val);
    int getPQntuples(void *res_val);
    int getPQfsize(void *res_val, int column_number_val);
    char *getTuplesValue(void *res_val, int row_number_val, int column_number_val);
    void doPQclear(void *res_val);
};
