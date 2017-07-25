/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../protocol_dir/net_port_protocol.h"
#include "../protocol_dir/web_fabric_protocol.h"
#include "test_class.h"

TestClass::TestClass(void)
{
    this->startNetConnect();
    this->debug(true, "init__", "");
}

TestClass::~TestClass(void)
{
}

void testObjectReceiveDataFromTransport (void *tp_transfer_object_val, void *test_object_val, void *data_val) {
    phwangLogit("Golbal::testObjectReceiveDataFromTransport", (char *) data_val);
    ((TestClass *) test_object_val)->exportedparseFunction((char *) data_val);
}

void TestClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, LINK_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, testObjectReceiveDataFromTransport, this, this->objectName());
}

void TestClass::startTest(void)
{
    for (int i = 1; i < 3; i++) {
        char *buf = (char *) malloc(128);
        int j = 0;
        buf[j++] = 'L';
        phwangEncodeNumber(&buf[j], i, 3);
        j += 3;
        buf[j++] = 'x';
        phwangEncodeNumber(&buf[j], i * 2, 3);
        this->transmitFunction(buf);
        sleep(1);
    }
}

void TestClass::logit (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void TestClass::abend (char const *str0_val, char const *str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
