/*
  Copyrights reserved
  Written by Paul Hwang
  File name: db_class.h
*/

#pragma once

class SqlClass;
class DbTestClass;

class DbClass {
    SqlClass *theSqlObject;
    DbTestClass *theDbTestObject;
    void *theSqlConnect;

    DbTestClass *dbTestObject(void) {return this->theDbTestObject;}

    int initDb(void);
    void *connectGoDb(void);
    void testDb(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);
   
public:
    DbClass(void);
    ~DbClass(void);

    SqlClass *sqlObject(void) {return this->theSqlObject;}
    void *sqlConnect(void) {return this->theSqlConnect;}
    char const *objectName(void) {return "DbClass";}
};
