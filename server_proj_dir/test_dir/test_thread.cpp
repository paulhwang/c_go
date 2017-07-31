/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_thread.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "test_class.h"

void *TestClassThreadFunction (void *fabric_object_val)
{
    ((TestClass *) fabric_object_val)->testThreadFunction();
}

void TestClass::startTestThread (void)
{
    this->debug(false, "startTestThread", "");

    int r = pthread_create(&this->theTestThread, 0, TestClassThreadFunction, this);
    if (r) {
        this->logit("startTestThread", "fail");
        return;
    }
}

void TestClass::testThreadFunction (void)
{
    this->debug(false, "testThreadFunction", "");
    this->runTestCase1();
}
