/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_PORT_CLASS_H__
#define __GO_PORT_CLASS_H__

class GoBaseClass;

class GoPortClass {
  public:
    GoPortClass(GoBaseClass* the_base_object);
    ~GoPortClass();

    char const* object_name();
    GoBaseClass* base_object();

  private:
    GoBaseClass *the_base_object;
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
