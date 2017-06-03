/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.h
*/

#pragma once
#include <pthread.h>

class TpClass;
class LinkMgrClass;
class BaseMgrClass;
class TpTransferClass;

class MainClass {
    TpClass *theTransportObject;
    LinkMgrClass *theLinkMgrObject;
    BaseMgrClass *theGoBaseMgrObject;

    pthread_t theLinkMgrTpServerThread;
    TpTransferClass *theLinkMgrTpTransferObject;

    pthread_t theBaseMgrTpServerThread;
    TpTransferClass *theBaseMgrTpTransferObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  public:
    MainClass(void);
    ~MainClass(void);
    char const *objectName(void) {return "MainClass";}
    TpClass *transportObject(void) {return this->theTransportObject;}

    /* exports */
    void exportBaseMgrReceiveDataFromTransport(void *data_val);
    void exportBaseMgrTransmitDataToTransport(void *data_val);
    void exportLinkMgrReceiveDataFromTransport(void *data_val);
    void exportLinkMgrTransmitDataToTransport(void *data_val);

    void startThreads(void);
    void goBaseMgrReceiveThreadLoop(void);
};
