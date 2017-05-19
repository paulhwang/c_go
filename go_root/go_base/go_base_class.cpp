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
#include "go_group_lst_class.h"
#include "go_base_class.h"
#include "go_game_class.h"

go_base_class::go_base_class (go_root_class* root_object_val) {
  this->the_root_object = root_object_val;
  this->the_engine_object = new GoEngineClass(this);
  this->the_board_object = new go_board_class(this);
  this->the_port_object = new go_port_class(this);
  this->the_config_object = new go_config_class(this);
  this->the_group_lst_object = new go_group_lst_class(this);
  this->the_game_object = new go_game_class(this);

  if (1) {
    this->logit("go_base_class", "init");
  }
}

go_base_class::~go_base_class () {
}

char const* go_base_class::object_name () {
  return "go_base_class";
}

go_root_class* go_base_class::root_object () {
  return this->the_root_object;
}

GoEngineClass* go_base_class::engine_object () {
  return this->the_engine_object;
}

void go_base_class::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void go_base_class::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

