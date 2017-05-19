/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "../go_root_class.h"
#include "./go_engine_class.h"
#include "./go_board_class.h"
#include "./go_port_class.h"
#include "./go_config_class.h"
#include "./go_group_lst_class.h"
#include "./go_base_class.h"

go_base_class::go_base_class (go_root_class* root_object_val) {
  this->the_root_object = root_object_val;
  this->the_engine_object = new go_engine_class(this);

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

go_engine_class* go_base_class::engine_object () {
  return this->the_engine_object;
}

void go_base_class::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void go_base_class::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

