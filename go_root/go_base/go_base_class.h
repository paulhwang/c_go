/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_BASE_CLASS_H__
#define __GO_BASE_CLASS_H__

class go_root_class;
class GoEngineClass;
class go_board_class;
class go_port_class;
class go_config_class;
class go_group_lst_class;
class go_game_class;

class GoBaseClass {
  public:
    GoBaseClass(go_root_class* root_object_val);
    ~GoBaseClass();
    go_root_class* root_object();

  private:
  	go_root_class* the_root_object;
  	GoEngineClass* the_engine_object;
    go_board_class* the_board_object;
    go_port_class* the_port_object;
    go_config_class* the_config_object;
    go_group_lst_class* the_group_lst_object;
    go_game_class* the_game_object;

    char const* object_name();
  	GoEngineClass* engine_object();

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
