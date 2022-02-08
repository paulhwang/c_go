/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_root.cpp
*/

#include "../phwang.h"
#include "db_root_class.h"
#include "/usr/include/postgresql/libpq-fe.h"

DbRootClass::DbRootClass (void)
{
    this->createDbs();
}

DbRootClass::~DbRootClass (void)
{
}

void DbRootClass::createDbs (void)
{
    this->createLoginDb();
}

void do_exit0(PGconn *conn) {
    
    PQfinish(conn);
}

void do_exit(PGconn *conn, PGresult *res) {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    PQclear(res);
    PQfinish(conn);    
}

void DbRootClass::createLoginDb (void)
{
    int lib_ver = PQlibVersion();

    printf("Version of libpq: %d\n", lib_ver);

    PGconn *conn = PQconnectdb("user=phwang dbname=login_db");
    if (PQstatus(conn) == CONNECTION_BAD) {
        
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        do_exit0(conn);
        return;
    }

    int ver = PQserverVersion(conn);
    printf("Server version: %d\n", ver);

    char *user = PQuser(conn);
    char *db_name = PQdb(conn);
    char *pswd = PQpass(conn);
    
    printf("User: %s\n", user);
    printf("Database name: %s\n", db_name);
    printf("Password: %s\n", pswd);
    
    PGresult *res = PQexec(conn, "DROP TABLE IF EXISTS Cars");
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);
    }
    
    PQclear(res);
    
    res = PQexec(conn, "CREATE TABLE Cars(Id INTEGER PRIMARY KEY," \
        "Name VARCHAR(20), Price INT)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res); 
    }
    
    PQclear(res);
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(1,'Audi',52642)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
        do_exit(conn, res);     
    
    PQclear(res);    
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(2,'Mercedes',57127)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);    
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(3,'Skoda',9000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(4,'Volvo',29000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);      
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(5,'Bentley',350000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(6,'Citroen',21000)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(7,'Hummer',41400)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);  
    
    res = PQexec(conn, "INSERT INTO Cars VALUES(8,'Volkswagen',21600)");
        
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        do_exit(conn, res);   
    }
    
    PQclear(res);  
    PQfinish(conn);
}


