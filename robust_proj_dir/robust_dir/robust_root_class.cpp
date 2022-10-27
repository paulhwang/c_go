/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_root_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "robust_root_class.h"

RobustRootClass::RobustRootClass (int debug_on_val)
{
    this->debugOn_ = debug_on_val;
    if (this->debugOn_) {
        printf("RobustRootClass::RobustRootClass() Robust test is on\n");
    }

   this->startTest(); 
}

RobustRootClass::~RobustRootClass (void)
{
}

void RobustRootClass::startTest(void)
{

}
