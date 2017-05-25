/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.h
*/

#ifndef __ENGINE_CLASS_H__
#define __ENGINE_CLASS_H__

#include <pthread.h>
class TransportClass;
class BaseMgrClass;
class QueueMgrClass;

class EngineClass {
    TransportClass *theTransportObject;
    BaseMgrClass *theGoBaseMgrObject;

    pthread_t theTransportThread;
    pthread_t transportThread(void);
    QueueMgrClass *theTransportTransmitQueue;

    pthread_t theGoThread;
    pthread_t goThread(void);
    QueueMgrClass *theGoReceiveQueue;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  public:
    EngineClass(void);
    ~EngineClass(void);

    char const *objectName(void) {return "EngineClass";}
    void startEngine(void);

    QueueMgrClass *transportTransmitQueue(void) {return theTransportTransmitQueue;}
    QueueMgrClass *goReceiveQueue(void) {return theGoReceiveQueue;}

    TransportClass *transportObject(void);
    void setTransportObject(TransportClass *val);
    BaseMgrClass* goBaseMgrObject(void);
    void setGoBaseMgrObject(BaseMgrClass *val);

    void createGoBaseMgrObject(void);
    void createTransportObject(void);
};

#endif
