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
class TpTransferClass;

class MainClass {
    TpClass *theTransportObject;
    LinkMgrClass *theLinkMgrObject;
    BaseMgrClass *theGoBaseMgrObject;

    TpTransferClass *link_mgr_tp_transfer_object;
    TpTransferClass *base_mgr_tp_transfer_object;

    pthread_t theGoThread;

    pthread_t goThread(void) {return theGoThread;}

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  public:
    MainClass(void);
    ~MainClass(void);
    char const *objectName(void) {return "MainClass";}

    void startThreads(void);
    void startEngineThreads(void);

    /* exports */
    void exportRreceiveDataFromTransport(void *data_val);
    void exportTransmitDataToTransport(void *data_val);

    /* thread loops */
    void goBaseMgrReceiveThreadLoop(void);
};
