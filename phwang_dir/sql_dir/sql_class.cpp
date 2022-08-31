/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_util_class.cpp
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
    PQfinish(this->goConnect());
}
 
void SqlClass::createTables (PGconn *conn_val) {
    this->createAccountTable(conn_val);
    this->createCarTable(conn_val);
}

void do_exit0(PGconn *conn) {
    
    PQfinish(conn);
}

void do_exit(PGconn *conn, PGresult *res) {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    PQclear(res);
    PQfinish(conn);    
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
        sprintf(buf, "Connection to database failed: %s\n", PQerrorMessage(this->goConnect()));
        this->logit("connectDb", buf);
        do_exit0(conn);
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

PGconn *SqlClass::connectGoDb (void)
{
    return this->connectDb("phwang", "go_db");
}

void SqlClass::createAccountTable (PGconn *conn_val)
{
    this->logit("createAccountTable", "");
    PGresult *res = PQexec(conn_val, "DROP TABLE IF EXISTS Accounts");
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res);
    }
    
    PQclear(res);
    
    res = PQexec(conn_val, "CREATE TABLE Accounts(Id INTEGER PRIMARY KEY," \
        "Name VARCHAR(20), Password VARCHAR(20))");

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res); 
    }
    
    PQclear(res);
}


void SqlClass::insertAccount (PGconn *conn_val) {
    PGresult *res;

    res = PQexec(conn_val, "INSERT INTO Accounts VALUES(1, 'admin','pp123')");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
        do_exit(conn_val, res);     
    
    PQclear(res);    

    res = PQexec(conn_val, "INSERT INTO Accounts VALUES(2, 'phwang','p123')");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
        do_exit(conn_val, res);     
    
    PQclear(res);    

/*
    res = PQexec(this->goConnect(), "INSERT INTO Accounts VALUES(3, 'paul','password_val')");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
        do_exit(this->goConnect(), res);     
    
    PQclear(res);    
*/

    res = PQexec(conn_val, "SELECT name FROM accounts;");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        do_exit(conn_val, res);
    }

    int i = 0;
    while (1) {
        char *data = PQgetvalue(res, i , 0);
        if (!data)
            break;
        printf("data=%s\n", data);
        i++;
    }

    PQclear(res);
}

void SqlClass::createCarTable(PGconn *conn_val) {
    this->logit("createCarTable", "");

    PGresult *res = PQexec(conn_val, "DROP TABLE IF EXISTS Cars");
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res);
    }
    
    PQclear(res);
    
    res = PQexec(conn_val, "CREATE TABLE Cars(Id INTEGER PRIMARY KEY," \
        "Name VARCHAR(20), Price INT)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res); 
    }
    
    PQclear(res);
    
    res = PQexec(conn_val, "INSERT INTO Cars VALUES(1,'Audi',52642)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
        do_exit(conn_val, res);     
    
    PQclear(res);    
    
    res = PQexec(conn_val, "INSERT INTO Cars VALUES(2,'Mercedes',57127)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res);   
    }
    
    PQclear(res);    
    
    res = PQexec(conn_val, "INSERT INTO Cars VALUES(3,'Skoda',9000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn_val, "INSERT INTO Cars VALUES(4,'Volvo',29000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res);   
    }
    
    PQclear(res);      
    
    res = PQexec(conn_val, "INSERT INTO Cars VALUES(5,'Bentley',350000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn_val, "INSERT INTO Cars VALUES(6,'Citroen',21000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn_val, "INSERT INTO Cars VALUES(7,'Hummer',41400)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn_val, "INSERT INTO Cars VALUES(8,'Volkswagen',21600)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn_val, res);   
    }
    
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
