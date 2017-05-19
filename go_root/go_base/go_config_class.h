/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_CONFIG_CLASS_H__
#define __GO_CONFIG_CLASS_H__

class GoBaseClass;

class go_config_class {
  public:
    go_config_class(GoBaseClass* the_base_object);
    ~go_config_class();

  private:
    GoBaseClass *the_base_object;
    char const* object_name();
    GoBaseClass* base_object();
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
