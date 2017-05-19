/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_ROOT_CLASS_H__
#define __GO_ROOT_CLASS_H__

class go_base_class;

class go_root_class {
  public:
    go_root_class();
    ~go_root_class();
    go_base_class* base_object();

  private:
    go_base_class* the_base_object;
    char const* object_name();
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif