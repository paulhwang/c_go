/*
  Copyrights reserved
  Written by Paul Hwang
  File name: sql_class.cpp
*/

#include "../phwang.h"
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
        this->logit("connectDb", buf);
    }

    sprintf(buf, "user=%s dbname=%s", user_val, dbname_val);
    PGconn *conn = PQconnectdb(buf);
    if (PQstatus(conn) == CONNECTION_BAD) {
        sprintf(buf, "Connection to database failed: %s\n", PQerrorMessage(conn));
        this->logit("connectDb", buf);
        this->disconnectDb(conn);
        return 0;
    }

    if (false) { // debug
        sprintf(buf, "Server version: %d", PQserverVersion(conn));
        this->logit("connectDb", buf);
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

void SqlClass::errPQexec(PGconn *conn_val, PGresult *res_val) {
    if (true) { // debug
        char buf[256];
        sprintf(buf, "%s\n", PQerrorMessage(conn_val));
        this->logit("errPQexec", buf);
    }

    PQclear(res_val);
    PQfinish(conn_val);    
}

int SqlClass::createTable (void *conn_val, char const *table_name_val, char const *data_val)
{
    char buf[256];
    this->debug(false, "createTable", table_name_val);

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
    this->debug(false, "createTable2", table_name_val);

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
    this->debug(false, "createTable3", table_name_val);

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
    this->debug(false, "dropTableIfExist", table_name_val);

    PGconn *conn = (PGconn *) conn_val;
    sprintf(buf, "DROP TABLE IF EXISTS %s", table_name_val);
    PGresult *res = PQexec(conn, buf);
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        this->errPQexec(conn, res);
    }
    
    PQclear(res);

    return 0;
}

void SqlClass::insertAccount (void *conn_val, char const *table_name_val, char const *values_val) {
    char buf[256];
    if (true) { //debug
        sprintf(buf, "INSERT INTO %s VALUES(%s)", table_name_val, values_val);
        this->debug(true, "insertAccount", buf);
    }

    PGconn *conn = (PGconn *) conn_val;
    sprintf(buf, "INSERT INTO %s VALUES(%s)", table_name_val, values_val);
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

int SqlClass::getPQntuples(void *res_val)
{
    PGresult *res = (PGresult *) res_val;
    return PQntuples(res);
}

int SqlClass::getPQfsize(void *res_val, int column_number_val)
{
    PGresult *res = (PGresult *) res_val;
    return PQfsize(res, column_number_val);
}

char *SqlClass::getTuplesValue(void *res_val, int row_number_val, int column_number_val)
{
    PGresult *res = (PGresult *) res_val;
    char *data = PQgetvalue(res, row_number_val , column_number_val);
    if (!data) {
        return 0;
    }

    this->debug(false, "getTuplesValue", data);
    return data;
}

void SqlClass::doPQclear(void *res_val)
{
    PGresult *res = (PGresult *) res_val;
    PQclear(res);    
}

void SqlClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void SqlClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
