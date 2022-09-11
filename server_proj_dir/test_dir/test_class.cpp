/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/malloc_dir/malloc_class.h"
#include "../protocol_dir/tcp_port_class.h"
#include "test_class.h"

TestClass::TestClass (void)
{
    memset(this, 0, sizeof(*this));
    this->startNetConnect();
    phwangDebugS(true, "TestClass::TestClass", "init");
}

TestClass::~TestClass (void)
{
}

void testObjectReceiveDataFromTransport (void *tp_transfer_object_val, void *test_object_val, void *data_val) {
    phwangLogitS("Golbal::testObjectReceiveDataFromTransport", (char *) data_val);
    ((TestClass *) test_object_val)->exportedparseFunction((char *) data_val);
}

void TestClass::startNetConnect (void)
{
    this->theTpTransferObject = phwangTpConnect(0, TcpPortClass::FABRIC_NODEJS_PORT_NUMER, testObjectReceiveDataFromTransport, this, this->objectName());
}

void TestClass::startTestThreads(void)
{
    for (int i = 0; i < 9; i++) {
        this->startTestThread();
    }
}

void TestClass::incrementAjaxId(int *ajax_id_ptr_val)
{
    (*ajax_id_ptr_val)++;
    if (*ajax_id_ptr_val >= 1000) {
        *ajax_id_ptr_val = 1;
    }
}

void TestClass::createName(int number_val, char *name_buf_val)
{
    char *data_ptr;
    data_ptr = name_buf_val;
    strcpy(data_ptr, "Name");
    data_ptr += strlen(name_buf_val);
    phwangEncodeNumber(data_ptr, number_val, 3);
    data_ptr += 3;
    *data_ptr = 0;
}

void TestClass::setupLink(int ajax_id_val, char *name_val)
{
    char *data_ptr;
    char *uplink_data = data_ptr = (char *) phwangMalloc(128, MallocClass::TEST_SETUP_LINK);
    int j = 0;
    *data_ptr++ = 'L';
    phwangEncodeNumber(data_ptr, ajax_id_val, 3);
    data_ptr += 3;
    strcpy(data_ptr, name_val);
    this->transmitFunction(uplink_data);
}
