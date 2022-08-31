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
    this->debug(false, "DbClass", "init");

    this->theSqlObject = new SqlClass();

    this->theSqlConnect = this->connectGoDb();
    if (this->sqlConnect() == 0) {
        this->abend("connectDbs", "fail to connnect to go_db");
        return;
    }

    this->createTables();
    this->insertAccount();
    this->insertCar();
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

void DbClass::createTables (void) {
    this->createAccountTable();
    this->createCarTable();
}

int DbClass::createAccountTable (void)
{
    int result = this->sqlObject()->dropTableIfExist(this->sqlConnect(), "accounts");
    if (result == -1) {
        return result;
    }

    return this->sqlObject()->createTable2(this->sqlConnect(), "accounts", "name VARCHAR(20)", "password VARCHAR(20)");
}


void DbClass::insertAccount (void) {
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "1, 'admin','p001'");
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "2, 'phwang','p002'");
    this->sqlObject()->insertAccount (this->sqlConnect(), "accounts", "3, 'paul','p003'");

    PGresult *res;
    res = this->sqlObject()->selectFrom(this->sqlConnect());
    if (!res) {
        return;
    }

    int i = 0;
    while (1) {
        char *data = this->sqlObject()->getTuplesValue(res, i , 0);
        if (!data)
            break;
        printf("data=%s\n", data);
        i++;
    }

    this->sqlObject()->pQclear(res);
}

int DbClass::createCarTable (void) {
    int result = this->sqlObject()->dropTableIfExist(this->sqlConnect(), "cars");
    if (result == -1) {
        return result;
    }

    return this->sqlObject()->createTable2(this->sqlConnect(), "cars", "name VARCHAR(20)", "price INT");
}

void DbClass::insertCar (void) {
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "1,'Audi',52642");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "2,'Mercedes',57127");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "3,'Skoda',9000");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "4,'Volvo',29000");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "5,'Bentley',350000");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "6,'Citroen',21000");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "7,'Hummer',41400");
    this->sqlObject()->insertAccount (this->sqlConnect(), "cars", "8,'Volkswagen',21600");
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
