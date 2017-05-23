/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.h
*/

#ifndef __ENGINE_CLASS_H__
#define __ENGINE_CLASS_H__

class EngineClass {
  public:
    EngineClass(void);
    ~EngineClass(void);

    char const* objectName(void);
    void startEngine(void);

  private:
    pthread_t  theGoThread;
    pthread_t  theTransportThread;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
