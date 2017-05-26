/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.h
*/

#pragma once
#include <pthread.h>
#include "utils_dir/logit.h"

class TransportClass;
class BaseMgrClass;
class QueueMgrClass;

class EngineClass {
    TransportClass *theTransportObject;
    pthread_t theTransportThread;
    QueueMgrClass *theTransportTransmitQueue;

    BaseMgrClass *theGoBaseMgrObject;
    pthread_t theGoThread;
    QueueMgrClass *theGoReceiveQueue;

    pthread_t transportThread(void) {return theTransportThread;}
    pthread_t goThread(void) {return theGoThread;}

    void logit (char const* str0_val, char const* str1_val) {LOGIT(str0_val, str1_val);}
    void abend (char const* str0_val, char const* str1_val) {ABEND(str0_val, str1_val);}

  public:
    EngineClass(void);
    ~EngineClass(void);

    void startEngine(void);

    /* exports */
    void receiveDataFromTransport(void *data_val);
    void transmitDataToTransport(void *data_val);

    /* thread loops */
    void transportTransmitThreadLoop(void);
    void goBaseMgrReceiveThreadLoop(void);

    char const *objectName(void) {return "EngineClass";}
    TransportClass *transportObject(void) {return theTransportObject;}
    BaseMgrClass* goBaseMgrObject(void) {return theGoBaseMgrObject;}
    QueueMgrClass *transportTransmitQueue(void) {return theTransportTransmitQueue;}
    QueueMgrClass *goReceiveQueue(void) {return theGoReceiveQueue;}
};
