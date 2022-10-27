/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/thread_dir/thread_root_class.h"
#include "robust_class.h"

RobustClass::RobustClass (int index_val, int debug_on_val)
{
    this->myIndex_ = index_val;
    this->debugOn_ = debug_on_val;
    if (this->debugOn_) {
        printf("RobustRootClass::RobustClass() myIndex_=%d\n", this->myIndex_);
    }
    this->startThread();
}

RobustClass::~RobustClass (void)
{
}

void *globalTestThreadFunc (void *val)
{
    RobustClass *robust_obj = (RobustClass *) val;
    robust_obj->testThreadFunc();
}

void *RobustClass::testThreadFunc (void)
{
    printf("RobustClass::testThreadFunc() myIndex_=%d\n", this->myIndex_);
}

void RobustClass::startThread(void)
{
    pthread_create(&this->testThread, 0, globalTestThreadFunc, this);
}
