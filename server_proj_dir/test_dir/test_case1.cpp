/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_case1.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../protocol_dir/net_port_protocol.h"
#include "../protocol_dir/web_fabric_protocol.h"
#include "test_class.h"

void TestClass::runTestCase1(void)
{
    int ajax_id = 1;
    char name[32];

    for (int i = 0; i < 100; i++) {
        this->createName(i, name);
        this->setupLink(ajax_id, name);
        this->incrementAjaxId(&ajax_id);
        if (i == 99) {
            i = 0;
        }
        sleep(5);
    }
}
