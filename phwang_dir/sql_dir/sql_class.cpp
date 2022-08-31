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

    if (1) { // debug
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

    if (0) { // debug
        sprintf(buf, "Server version: %d", PQserverVersion(conn));
        this->logit("connectDb", buf);
    }

    if (0) { // debug
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
