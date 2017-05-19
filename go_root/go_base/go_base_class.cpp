/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "../go_root_class.h"
#include "go_engine_class.h"
#include "go_board_class.h"
#include "go_port_class.h"
#include "go_config_class.h"
#include "go_base_class.h"
#include "go_game_class.h"

GoBaseClass::GoBaseClass (go_root_class* root_object_val) {
  this->the_root_object = root_object_val;
  this->the_engine_object = new GoEngineClass(this);
  this->the_board_object = new go_board_class(this);
  this->the_port_object = new go_port_class(this);
  this->the_config_object = new go_config_class(this);
  this->the_game_object = new go_game_class(this);

  if (1) {
    this->logit("GoBaseClass", "init");
  }
}

GoBaseClass::~GoBaseClass () {
}

char const* GoBaseClass::object_name () {
  return "GoBaseClass";
}

go_root_class* GoBaseClass::root_object () {
  return this->the_root_object;
}

GoEngineClass* GoBaseClass::engine_object () {
  return this->the_engine_object;
}

void GoBaseClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoBaseClass::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

