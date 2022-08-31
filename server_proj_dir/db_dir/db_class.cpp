/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/sql_dir/sql_class.h"
#include "db_class.h"

DbClass::DbClass (void)
{
    memset(this, 0, sizeof(*this));
    this->debug(true, "DbClass", "init");

    this->theSqlObject = new SqlClass();

    this->theGoConnect = this->connectGoDb();
    if (this->goConnect() == 0) {
        this->abend("connectDbs", "fail to connnect to go_db");
        return;
    }

    this->createTables(this->theGoConnect);
    this->insertAccount(this->theGoConnect);

}

DbClass::~DbClass (void)
{
}

void do_exit(PGconn *conn, PGresult *res) {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    PQclear(res);
    PQfinish(conn);    
}

PGconn *DbClass::connectGoDb (void)
{
    return this->sqlObject()->connectDb("phwang", "go_db");
}

void DbClass::createTables (PGconn *conn_val) {
    this->createAccountTable(conn_val);
    this->createCarTable(conn_val);
}

void DbClass::createAccountTable (PGconn *conn_val)
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


void DbClass::insertAccount (PGconn *conn_val) {
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

void DbClass::createCarTable(PGconn *conn_val) {
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

void DbClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void DbClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
