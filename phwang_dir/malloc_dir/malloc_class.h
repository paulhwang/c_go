/*
  Copyrights reserved
  Written by Paul Hwang
  File name: malloc_class.h
*/

#pragma once

class MallocClass
{
    char const *objectName(void) {return "MallocClass";}

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    MallocClass(void);
    ~MallocClass(void);
    
    int const static SIGN_UP  = 0;
    int const static SIGN_IN  = 1;
    int const static DATAGRAM  = 2;

    void *phwangMalloc1(int size_val, int who_val);
    void *phwangMalloc(int size_val, char const *who_val);
    void phwangFree(void *data_val, char const *who_val);
};
