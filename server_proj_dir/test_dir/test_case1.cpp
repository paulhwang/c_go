/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_case1.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "test_class.h"

int theTestCase1NameIndex = 0;

void TestClass::runTestCase1 (void)
{
    int ajax_id = 1;
    char name[32];
    int name_index = theTestCase1NameIndex;
    theTestCase1NameIndex += 100;

    for (int i = name_index; i < (name_index + 100); i++) {
        this->createName(i, name);
        this->setupLink(ajax_id, name);
        this->incrementAjaxId(&ajax_id);
        if (i == 99) {
            i = 0;
        }
        phwangDebugS(true, "TestClass::runTestCase1", name);
        sleep(5);
    }
}
