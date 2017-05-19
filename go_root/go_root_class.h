/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_ROOT_CLASS_H__
#define __GO_ROOT_CLASS_H__

class GoBaseClass;

class goRootClass {
  public:
    goRootClass();
    ~goRootClass();

    char const* objectName();
    GoBaseClass* baseObject();

  private:
    GoBaseClass* theBaseObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif