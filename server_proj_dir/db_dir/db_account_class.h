/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_class.h
*/

#pragma once

class SqlClass;
class DbAccountEntryClass;
//class DbClass;

class DbAccountClass {
    SqlClass *theSqlObject;
    DbClass *theDbObject;
    void *theSqlConnect;
    int theAccountIndex;

    DbClass *dbObject(void) {return this->theDbObject;}
    SqlClass *sqlObject(void);
    void *sqlConnect(void);
    int accountIndex(void) {return this->theAccountIndex;}
    void incrementAccountIndex(void) {this->theAccountIndex++;}

    void createAccountTableInDatabase(void);
    void createAccount(char const *name_val, char const *psword_val, char const *email_val);
    void listAccount (void);
    void developTest(void);
   
public:
    DbAccountClass(DbClass *db_object_val);
    ~DbAccountClass(void);

    char const *objectName(void) {return "DbAccountClass";}

    void insertAccountEntry(DbAccountEntryClass *entry_val);

    void checkAccountNameExist (
        char const *account_name_val,
        char *result_ptr);
    void checkPassword(
        char const *account_name_val,
        char const *password_val,
        char *result_ptr);
};
