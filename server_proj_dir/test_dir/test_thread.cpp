/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_thread.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "test_class.h"

void *TestClassThreadFunction (void *fabric_object_val)
{
    return ((TestClass *) fabric_object_val)->testThreadFunction();
}

void TestClass::startTestThread (void)
{
    phwangDebugS(false, "TestClass::startTestThread", "");

    int r = phwangPthreadCreate(&this->theTestThread, 0, TestClassThreadFunction, this);
    if (r) {
        phwangLogitS("TestClass::startTestThread", "fail");
        return;
    }
}

void *TestClass::testThreadFunction (void)
{
    phwangDebugS(false, "TestClass::testThreadFunction", "");
    this->runTestCase1();
    return 0;
}
