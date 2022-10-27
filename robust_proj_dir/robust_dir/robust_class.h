/*
  Copyrights reserved
  Written by Paul Hwang
  File name: robust_root_class.h
*/

#pragma once

#include <pthread.h>

class RobustClass {
    int myIndex_;
    int debugOn_;
    pthread_t testThread;
    void *portObj_;

    void startThread(void);
    void startNetConnect(void);

public:
    RobustClass(int index_val, int debug_on_val);
    ~RobustClass(void);

    void *testThreadFunc(void);
    void rcvFunc(char *data_val);

};
