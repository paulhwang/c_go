/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_GAME_CLASS_H__
#define __GO_GAME_CLASS_H__

class go_base_class;

class go_game_class {
  public:
    go_game_class(go_base_class* the_base_object);
    ~go_game_class();

  private:
    go_base_class *the_base_object;
    char const* object_name();
    go_base_class* base_object();
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
