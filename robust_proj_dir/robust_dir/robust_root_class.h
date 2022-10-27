/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_root_class.h
*/

#pragma once

#include <pthread.h>

class ThreadRootClass;

class RobustRootClass {
    int  const static TEST_THREAD_COUNT = 3;

    int debugOn_;
    ThreadRootClass *threadRoodObj_;
    pthread_t testThreads[TEST_THREAD_COUNT];

    int debugOn(void) {return this->debugOn_;}
    void startTestThreads(int thread_count_val);

public:
    RobustRootClass(int debug_on_val);
    ~RobustRootClass(void);
};
