/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_root_class.h
*/

#pragma once

class RobustRootClass {

  public:
    RobustRootClass(int debug_code_val);
    ~RobustRootClass(void);
    char const *objectName(void) {return "RobustRootClass";}
};
