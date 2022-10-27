/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_root_class.h
*/

#pragma once

class ThreadRootClass;

class RobustRootClass {
    int  const static TEST_THREAD_COUNT = 3;

    int debugOn_;
    void startTestThreads(void);

public:
    RobustRootClass(int debug_on_val);
    ~RobustRootClass(void);
};
