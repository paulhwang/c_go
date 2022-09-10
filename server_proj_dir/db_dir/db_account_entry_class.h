/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_entry_class.h
*/

#pragma once

#include <atomic>

class DbAccountEntryClass {
    char const *objectName(void) {return "DbAccountEntryClass";}

    char *theAccountName;
    char *thePassword;
    char *theEmail;
   
public:
    DbAccountEntryClass(void);
    ~DbAccountEntryClass(void);
    static std::atomic<int> ObjectCount;

    char *accountName(void) {return this->theAccountName;}
    void setAccountName(char *account_name_val) {this->theAccountName = account_name_val;}
    char *password(void) {return this->thePassword;}
    void setPassword(char *password_val) {this->thePassword = password_val;}
    char *email(void) {return this->theEmail;}
    void setEmail(char *email_val) {this->theEmail = email_val;}

};
