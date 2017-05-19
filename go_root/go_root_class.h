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
    GoBaseClass* base_object();

  private:
    GoBaseClass* the_base_object;
    char const* object_name();
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif