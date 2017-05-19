/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_CONFIG_CLASS_H__
#define __GO_CONFIG_CLASS_H__

class GoBaseClass;

class GoConfigClass {
  public:
    GoConfigClass(GoBaseClass* the_base_object);
    ~GoConfigClass();

    char const* objectName();
    GoBaseClass* baseObject();

  private:
    GoBaseClass *theBaseObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
