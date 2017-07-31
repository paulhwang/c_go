/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_class.h
*/

#pragma once
#include <pthread.h>

class TestClass {
    void *theTpTransferObject;
    pthread_t theTestThread;

    void startNetConnect(void);
    void startTestThread (void);

    void incrementAjaxId(int *ajax_id_ptr_val);
    char *createName(int number_val, char *name_buf_val);
    void setupLink(int ajax_id_val, char *name_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);}
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    TestClass(void);
    ~TestClass(void);
    char const *objectName(void) {return "TestClass";}

    void testThreadFunction (void);
    void transmitFunction(char *data_val);

    /* exports */
    void startTest(void);
    void exportedparseFunction(char *data_val);
};
