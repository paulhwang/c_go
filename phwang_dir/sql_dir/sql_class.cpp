/*
  Copyrights reserved
  Written by Paul Hwang
  File name: sql_class.cpp
*/

#include "../phwang.h"
#include "../abend_dir/abend_class.h"
#include "sql_class.h"
#include "/usr/include/postgresql/libpq-fe.h"

SqlClass::SqlClass (void)
{
    memset(this, 0, sizeof(*this));
}

SqlClass::~SqlClass (void)
{
}

PGconn *SqlClass::connectDb (char const *user_val, char const *dbname_val)
{
    char buf[128];

    if (false) { // debug
        sprintf(buf, "Version of libpq: %d", PQlibVersion());
        phwangLogitS("SqlClass::connectDb", buf);
    }

    sprintf(buf, "user=%s dbname=%s", user_val, dbname_val);
    PGconn *conn = PQconnectdb(buf);
    if (PQstatus(conn) == CONNECTION_BAD) {
        sprintf(buf, "Connection to database failed: %s\n", PQerrorMessage(conn));
        phwangLogitS("SqlClass::connectDb", buf);
        this->disconnectDb(conn);
        return 0;
    }

    if (false) { // debug
        sprintf(buf, "Server version: %d", PQserverVersion(conn));
        phwangLogitS("SqlClass::connectDb", buf);
    }

    if (false) { // debug
        printf("User: %s\n", PQuser(conn));
        printf("Database name: %s\n", PQdb(conn));
        printf("Password: %s\n", PQpass(conn));
    }

    return conn;
}

void SqlClass::disconnectDb (void *conn_val)
{
    PGconn *conn = (PGconn *) conn_val;
    PQfinish(conn);
}

void SqlClass::errPQexec (PGconn *conn_val, PGresult *res_val) {
    phwangLogitS("SqlClass::errPQexec", PQerrorMessage(conn_val));

    //PQclear(res_val); cause double free
    PQfinish(conn_val);    
}

int SqlClass::createTable (void *conn_val, char const *table_name_val, char const *data_val)
{
    char buf[256];
    phwangDebugS(false, "SqlClass::createTable", table_name_val);

    PGconn *conn = (PGconn *) conn_val;
    sprintf(buf, "CREATE TABLE %s(Id INTEGER PRIMARY KEY, %s)", table_name_val, data_val);
    PGresult *res = PQexec(conn, buf);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        this->errPQexec(conn, res);
        PQclear(res);
        return -1;
    }

    PQclear(res);
    return 0;
}

int SqlClass::createTable2 (void *conn_val, char const *table_name_val, char const *val1, char const *val2)
{
    char buf[256];
    phwangDebugS(false, "SqlClass::createTable2", table_name_val);

    PGconn *conn = (PGconn *) conn_val;
    sprintf(buf, "CREATE TABLE %s(Id INTEGER PRIMARY KEY, %s, %s)", table_name_val, val1, val2);
    PGresult *res = PQexec(conn, buf);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        this->errPQexec(conn, res);
        PQclear(res);
        return -1;
    }

    PQclear(res);
    return 0;
}

int SqlClass::createTable3 (void *conn_val, char const *table_name_val, char const *val1, char const *val2, char const *val3)
{
    char buf[256];
    phwangDebugS(false, "SqlClass::createTable3", table_name_val);

    PGconn *conn = (PGconn *) conn_val;
    sprintf(buf, "CREATE TABLE %s(Id INTEGER PRIMARY KEY, %s, %s, %s)", table_name_val, val1, val2, val3);
    PGresult *res = PQexec(conn, buf);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        this->errPQexec(conn, res);
        PQclear(res);
        return -1;
    }

    PQclear(res);
    return 0;
}

int SqlClass::dropTableIfExist (void *conn_val, char const *table_name_val)
{
    char buf[256];
    phwangDebugS(false, "SqlClass::dropTableIfExist", table_name_val);

    PGconn *conn = (PGconn *) conn_val;
    sprintf(buf, "DROP TABLE IF EXISTS %s", table_name_val);
    PGresult *res = PQexec(conn, buf);
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        this->errPQexec(conn, res);
    }
    
    PQclear(res);

    return 0;
}

void SqlClass::insertInto (void *conn_val, char const *table_name_val, char const *values_val) {
    char buf[1024];

    sprintf(buf, "INSERT INTO %s VALUES(%s)", table_name_val, values_val);
    phwangDebugS(false, "SqlClass::insertInto", buf);

    PGconn *conn = (PGconn *) conn_val;
    PGresult *res = PQexec(conn, buf);
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        this->errPQexec(conn, res);
    }

    PQclear(res);    
}

PGresult *SqlClass::selectFrom (void *conn_val, char const *column_val) {
    PGconn *conn = (PGconn *) conn_val;
    char buf[256];

    sprintf(buf, "SELECT %s FROM accounts;", column_val);
    PGresult *res = PQexec(conn, buf);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        this->errPQexec(conn, res);
        return 0;
    }
    return res;
}

int SqlClass::getPQntuples (void *res_val)
{
    PGresult *res = (PGresult *) res_val;
    return PQntuples(res);
}

int SqlClass::getPQfsize (void *res_val, int column_number_val)
{
    PGresult *res = (PGresult *) res_val;
    return PQfsize(res, column_number_val);
}

char *SqlClass::getTuplesValue (void *res_val, int row_number_val, int column_number_val)
{
    PGresult *res = (PGresult *) res_val;
    char *data = PQgetvalue(res, row_number_val , column_number_val);
    if (!data) {
        return 0;
    }

    phwangDebugS(false, "SqlClass::getTuplesValue", data);
    return data;
}

void SqlClass::doPQclear (void *res_val)
{
    PGresult *res = (PGresult *) res_val;
    PQclear(res);    
}
