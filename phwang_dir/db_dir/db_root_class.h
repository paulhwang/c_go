/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_root.h
*/

#pragma once

class DbRootClass {
    void createDbs(void);
    void createLoginDb(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);
   
public:
    DbRootClass(void);
    ~DbRootClass(void);
    char const *objectName(void) {return "DbRootClass";}

    /* exports */
};
