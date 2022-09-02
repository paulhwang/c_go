/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_account_entry_class.h
*/

#pragma once

class DbAccountEntryClass {
    char *theAccountName;
    char *thePassword;
    char *theEmail;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);
   
public:
    DbAccountEntryClass(void);
    ~DbAccountEntryClass(void);

    char const *objectName(void) {return "DbAccountDataClass";}

    char *accountName(void) {return this->theAccountName;}
    void setAccountName(char *account_name_val) {this->theAccountName = account_name_val;}
    char *password(void) {return this->thePassword;}
    void setPassword(char *password_val) {this->thePassword = password_val;}
    char *email(void) {return this->theEmail;}
    void setEmail(char *email_val) {this->theEmail = email_val;}

};
