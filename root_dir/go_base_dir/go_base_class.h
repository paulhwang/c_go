/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.h
*/

#pragma once

class BaseMgrClass;
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
    BaseMgrClass* theBaseMgrObject;
    GoEngineClass* theEngineObject;
    GoBoardClass* theBoardObject;
    GoPortClass* thePortObject;
    GoConfigClass* theConfigObject;
    GoGameClass* theGameObject;

  public:
    GoBaseClass(BaseMgrClass* base_mgr_object_val);
    ~GoBaseClass(void);

    BaseMgrClass* baseMgrObject(void);

    void goBaseLogit(char const* str0_val, char const* str1_val) {LOGIT(str0_val, str1_val);}
    void goBaseAbend(char const* str0_val, char const* str1_val) {ABEND(str0_val, str1_val);}

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

    GoEngineClass* engineObject(void) {return theEngineObject;}
    GoBoardClass* boardObject(void) {return theBoardObject;}
    GoPortClass* portObject(void) {return thePortObject;}
    GoConfigClass* configObject(void) {return theConfigObject;}
    GoGameClass* gameObject(void) {return theGameObject;}
    char const* objectName(void) {return "GoBaseClass";}
};
