/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_root_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "robust_root_class.h"
#include "robust_class.h"

RobustRootClass::RobustRootClass (int debug_on_val)
{
    this->debugOn_ = debug_on_val;
    this->startTestThreads(); 
}

RobustRootClass::~RobustRootClass (void)
{
}

void RobustRootClass::startTestThreads(void)
{
    for (int i = 0; i < RobustRootClass::TEST_THREAD_COUNT; i++) {
        new RobustClass(i, this->debugOn_);
    }
}
