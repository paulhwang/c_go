/*
  Copyrights reserved
  Written by Paul Hwang
  File name: malloc_class.h
*/

#pragma once

#define MALLOC_CLASS_USER_TABLE_SIZE 20

class MallocClass
{
    char const *objectName(void) {return "MallocClass";}

    int theUserTable[MALLOC_CLASS_USER_TABLE_SIZE];

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    MallocClass(void);
    ~MallocClass(void);
    
    int const static TP_TRANSMIT  = 0;
    int const static TP_RECEIVE_THREAD  = 2;
    int const static TP_RECEIVE  = 1;
    int const static TP_RECEIVE2  = 2;
    int const static ENCODE_STRING  = 3;
    int const static DECODE_STRING  = 4;
    int const static SIGN_UP  = 5;
    int const static SIGN_IN  = 6;
    int const static DATAGRAM  = 7;
    int const static DB_ACCOUNT_DEFAULT_NAME = 8;

    void *phwangMalloc1(int size_val, int who_val);
    void *phwangMalloc(int size_val, char const *who_val);
    void phwangFree(void *data_val);
};
