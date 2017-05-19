/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "go_base_class.h"
#include "go_config_class.h"

go_config_class::go_config_class (GoBaseClass* base_object_val) {
  this->the_base_object = base_object_val;

  if (1) {
    this->logit("go_config_class", "init");
  }
}

go_config_class::~go_config_class () {
}

char const* go_config_class::object_name () {
  return "go_config_class";
}

GoBaseClass* go_config_class::base_object () {
  return this->the_base_object;
}

void go_config_class::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void go_config_class::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

