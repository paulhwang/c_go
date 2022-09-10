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
    void runTestCase1(void);

    void incrementAjaxId(int *ajax_id_ptr_val);
    void createName(int number_val, char *name_buf_val);
    void setupLink(int ajax_id_val, char *name_val);

public:
    TestClass(void);
    ~TestClass(void);
    char const *objectName(void) {return "TestClass";}

    void *testThreadFunction(void);
    void transmitFunction(char *data_val);

    /* exports */
    void startTestThreads(void);
    void exportedparseFunction(char *data_val);
};
