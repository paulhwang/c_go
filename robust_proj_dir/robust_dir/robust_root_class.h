/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_root_class.h
*/

#pragma once

class RobustRootClass {
  int debugOn_;
  int debugOn(void) {return this->debugOn_;}
  void startTest(void);

  public:
    RobustRootClass(int test_on_val, int debug_on_val);
    ~RobustRootClass(void);
};
