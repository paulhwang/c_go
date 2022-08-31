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

    if (true) { // debug
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

void SqlClass::disconnectDb (PGconn *conn_val)
{
    PQfinish(conn_val);
}

void do_exit111(PGconn *conn, PGresult *res) {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    PQclear(res);
    PQfinish(conn);    
}

int SqlClass::createTable2 (PGconn *conn_val, char const *table_name_val, char const *val1, char const *val2)
{
    char buf[256];
    this->debug(true, "createTable", table_name_val);

    sprintf(buf, "CREATE TABLE %s(Id INTEGER PRIMARY KEY, %s, %s)", table_name_val, val1, val2);
    PGresult *res = PQexec(conn_val, buf);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit111(conn_val, res);
        PQclear(res);
        return -1;
    }

    PQclear(res);
    return 0;
}

int SqlClass::dropTableIfExist (PGconn *conn_val, char const *table_name_val)
{
    char buf[256];
    this->logit("dropTableIfExist", table_name_val);

    sprintf(buf, "DROP TABLE IF EXISTS %s", table_name_val);
    PGresult *res = PQexec(conn_val, buf);
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit111(conn_val, res);
    }
    
    PQclear(res);

    return 0;
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
