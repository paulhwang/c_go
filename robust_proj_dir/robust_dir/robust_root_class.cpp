/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_root_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/thread_dir/thread_root_class.h"
#include "robust_root_class.h"

RobustRootClass::RobustRootClass (int debug_on_val)
{
    this->debugOn_ = debug_on_val;
    if (this->debugOn_) {
        printf("RobustRootClass::RobustRootClass() Robust test is on\n");
    }

    this->threadRoodObj_ = new ThreadRootClass(debug_on_val);

    this->startTestThreads(RobustRootClass::TEST_THREAD_COUNT); 
}

RobustRootClass::~RobustRootClass (void)
{
}

int global_index = 0;

void *testThreadFunction (void *val)
{
    int my_index = global_index++;
    printf("%d\n", my_index);
}

void RobustRootClass::startTestThreads(int thread_count_val)
{
    for (int i = 0; i < thread_count_val; i++) {
        this->threadRoodObj_->pthreadCreate(&this->testThreads[i], 0, testThreadFunction, this);
    }
}
