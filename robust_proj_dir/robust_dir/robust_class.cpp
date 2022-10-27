/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/thread_dir/thread_root_class.h"
#include "../../server_proj_dir/define_dir/tcp_port_define.h"
#include "robust_class.h"

RobustClass::RobustClass (int index_val, int debug_on_val)
{
    this->myIndex_ = index_val;
    this->debugOn_ = debug_on_val;
    this->startThread();
}

RobustClass::~RobustClass (void)
{
}

void *globalTestThreadFunc (void *robust_obj_val)
{
    RobustClass *robust_obj = (RobustClass *) robust_obj_val;
    robust_obj->testThreadFunc();
    return 0;
}

void RobustClass::startThread(void)
{
    pthread_create(&this->testThread, 0, globalTestThreadFunc, this);
}

void *RobustClass::testThreadFunc (void)
{
    if (this->debugOn_) {
        printf("RobustClass::testThreadFunc() myIndex_=%d\n", this->myIndex_);
    }
    this->startNetConnect();
    return 0;
}

void globalRcvFunc (void *port_object_val, void *robust_obj_val, void *data_val) {
    RobustClass *robust_obj = (RobustClass*) robust_obj_val;
    robust_obj->rcvFunc((char *) data_val);
    phwangFree(data_val);
}

void RobustClass::rcvFunc (char *data_val)
{
    if (true && this->debugOn_) {
        printf("RobustClass::rcvFunc() data=%s\n", data_val);
    }
}

void RobustClass::startNetConnect (void)
{
    this->portObj_ = phwangTpConnect(0, TcpPortDefine::FABRIC_TEST_PORT_NUMER, globalRcvFunc, this, "this->objectName()");
}
