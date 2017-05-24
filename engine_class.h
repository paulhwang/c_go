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

class EngineClass {
  public:
    EngineClass(void);
    ~EngineClass(void);

    char const *objectName(void);
    void startEngine(void);

    TransportClass *transportObject(void);
    void setTransportObject(TransportClass *val);
    BaseMgrClass* goBaseMgrObject(void);
    void setGoBaseMgrObject(BaseMgrClass *val);

    void createGoBaseMgrObject(void);
    void createTransportObject(void);

  private:
    TransportClass *theTransportObject;
    BaseMgrClass *theGoBaseMgrObject;

    pthread_t theGoThread;
    pthread_t theTransportThread;

    pthread_t goThread(void);
    pthread_t transportThread(void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
