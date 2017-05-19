/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_MOVE_CLASS_H__
#define __GO_MOVE_CLASS_H__

class go_base_class;

class go_move_class {
  public:
    go_move_class();
    ~go_move_class();

  private:
    char const* object_name();
    go_base_class* base_object();
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
