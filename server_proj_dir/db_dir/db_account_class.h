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
    void createAccount(char *name_val, char *psword_val, char *email_val);
    void listAccount (void);
    void developTest(void);

    void debug(int debug_on_val, char const *func_name_val, char const *str1_val);
    void debug2(int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val);
    void debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val);
    void debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void logit(char const *func_name_val, char const *str1_val);
    void logit2(char const *func_name_val, char const *str1_val, char const *str2_val);
    void logitInt(char const *func_name_val, char const *str1_val, int int1_val);
    void logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void abend(char const *func_name_val, char const *str1_val);
    void abend2(char const *func_name_val, char const *str1_val, char const *str2_val);
   
public:
    DbAccountClass(DbClass *db_object_val);
    ~DbAccountClass(void);

    char const *objectName(void) {return "DbAccountClass";}

    void insertAccountEntry(DbAccountEntryClass *entry_val);
    int checkAccountNameExist (char const *account_name_val);
    int checkPassword(char const *account_name_val, char const *password_val);

    int const static DB_ACCOUNT_SUCCEED            = 0;
    int const static DB_ACCOUNT_SELECT_FAIL        = 1;
    int const static DB_ACCOUNT_EMPTY_TABLE        = 2;
    int const static DB_ACCOUNT_NAME_EXIST         = 3;
    int const static DB_ACCOUNT_NAME_NOT_EXIST     = 4;
    int const static DB_ACCOUNT_PASSWORD_MATCH     = 5;
    int const static DB_ACCOUNT_PASSWORD_NOT_MATCH = 6;
};
