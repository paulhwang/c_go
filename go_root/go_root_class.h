/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_ROOT_CLASS_H__
#define __GO_ROOT_CLASS_H__

class GoBaseClass;
class TransportClass;

class GoRootClass {
  public:
    GoRootClass();
    ~GoRootClass();

    char const* objectName();
    GoBaseClass* baseObject();
    TransportClass* transportObject();

  private:
    GoBaseClass* theBaseObject;
    TransportClass* theTransportObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif