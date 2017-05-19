/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_BASE_CLASS_H__
#define __GO_BASE_CLASS_H__

class go_root_class;
class go_engine_class;

class go_base_class {
  public:
    go_base_class(go_root_class* root_object_val);
    ~go_base_class();
    go_root_class* root_object();

  private:
  	go_root_class* the_root_object;
  	go_engine_class* the_engine_object;

    char const* object_name();
  	go_engine_class* engine_object();

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
