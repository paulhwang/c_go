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
    go_root_class* rootObject();

  private:
  	go_root_class* theRootObject;
  	GoEngineClass* theEngineObject;
    go_board_class* theBoardObject;
    go_port_class* thePortObject;
    go_config_class* theConfigObject;
    go_game_class* theGameObject;

    char const* objectName();
  	GoEngineClass* engineObject();

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
