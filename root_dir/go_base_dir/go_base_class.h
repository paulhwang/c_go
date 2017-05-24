/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.h
*/

#ifndef __GO_BASE_CLASS_H__
#define __GO_BASE_CLASS_H__

#include "../base_mgr_dir/base_mgr_class.h"
#include "go_define.h"
#include "go_board_class.h"
#include "go_engine_class.h"
#include "go_port_class.h"
#include "go_config_class.h"
#include "go_game_class.h"
#include "go_group_class.h"
#include "go_group_list_class.h"
#include "go_move_class.h"

class GoBaseClass {
  public:
    GoBaseClass();
    ~GoBaseClass(void);

    char const* objectName(void);
    BaseMgrClass* baseMgrObject(void);
    GoEngineClass* engineObject(void);
    GoBoardClass* boardObject(void);
    GoPortClass* portObject(void);
    GoConfigClass* configObject(void);
    GoGameClass* gameObject(void);

    void goBaseLogit(char const* str0_val, char const* str1_val);
    void goBaseAbend(char const* str0_val, char const* str1_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  private:
  	BaseMgrClass* theBaseMgrObject;
  	GoEngineClass* theEngineObject;
    GoBoardClass* theBoardObject;
    GoPortClass* thePortObject;
    GoConfigClass* theConfigObject;
    GoGameClass* theGameObject;
};
#endif
