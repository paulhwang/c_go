/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.h
*/

#pragma once
#include <pthread.h>
#include "utils_dir/logit.h"

class TpClass;
class LinkMgrClass;
class BaseMgrClass;
class QueueMgrClass;
class TpServerClass;

class MainClass {
    TpClass *transportObject;
    LinkMgrClass *linkMgrObject;
    BaseMgrClass *goBaseMgrObject;

    QueueMgrClass *theTransportTransmitQueue;

    TpServerClass *link_mgr_server_class;
    TpServerClass *base_mgr_server_class;

    pthread_t theGoThread;

    pthread_t goThread(void) {return theGoThread;}

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  public:
    MainClass(void);
    ~MainClass(void);

    void startThreads(void);
    void startEngineThreads(void);

    /* exports */
    void exportRreceiveDataFromTransport(void *data_val);
    void exportTransmitDataToTransport(void *data_val);

    /* thread loops */
    void goBaseMgrReceiveThreadLoop(void);

    char const *objectName(void) {return "MainClass";}
    QueueMgrClass *transportTransmitQueue(void) {return theTransportTransmitQueue;}
};
