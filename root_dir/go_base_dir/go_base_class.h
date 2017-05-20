/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_BASE_CLASS_H__
#define __GO_BASE_CLASS_H__

#include "../root_class.h"
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
    GoBaseClass(GoRootClass* root_object_val);
    ~GoBaseClass();

    char const* objectName();
    GoRootClass* rootObject();
    GoEngineClass* engineObject();
    GoBoardClass* boardObject();
    GoPortClass* portObject();
    GoConfigClass* configObject();
    GoGameClass* gameObject();

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  private:
  	GoRootClass* theRootObject;
  	GoEngineClass* theEngineObject;
    GoBoardClass* theBoardObject;
    GoPortClass* thePortObject;
    GoConfigClass* theConfigObject;
    GoGameClass* theGameObject;
};
#endif
