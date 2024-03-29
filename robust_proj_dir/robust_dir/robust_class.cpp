/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/thread_dir/thread_root_class.h"
#include "../../server_proj_dir/define_dir/tcp_port_define.h"
#include "robust_class.h"

RobustClass::RobustClass (int debug_on_val, int index_val)
{
    memset(this, 0, sizeof(*this));
    this->debugOn_ = true && debug_on_val;
    this->myIndex_ = index_val;
    this->setObjetName("robust", 2);
    this->startThread();
}

RobustClass::~RobustClass (void)
{
}

void RobustClass::setObjetName (char const *name_val, int index_size_val)
{
    int len = strlen(name_val);
    memcpy(this->objectName_, "robust", len);
    phwangEncodeNumber(&this->objectName_[len], this->myIndex_, index_size_val);
    this->objectName_[len + index_size_val] = 0;
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
    if (false && this->debugOn_) {
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
    this->portObj_ = phwangTpConnect(0, TcpPortDefine::FABRIC_TEST_PORT_NUMER, globalRcvFunc, this, this->objectName());
}
