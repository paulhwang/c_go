/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_class.h
*/

#pragma once

class SqlClass;
//class DbClass;

class DbAccountClass {
    SqlClass *theSqlObject;
    DbClass *theDbObject;
    void *theSqlConnect;

    DbClass *dbObject(void) {return this->theDbObject;}
    SqlClass *sqlObject(void);
    void *sqlConnect(void);

    void createAccountTableInDatabase(void);
    void listAccount (void);
    void developTest(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);
   
public:
    DbAccountClass(DbClass *db_object_val);
    ~DbAccountClass(void);

    char const *objectName(void) {return "DbAccountClass";}

    int checkPassword(char const *password_val);
};
