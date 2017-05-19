/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "go_base_class.h"
#include "go_port_class.h"

go_port_class::go_port_class (GoBaseClass* base_object_val) {
  this->the_base_object = base_object_val;

  if (1) {
    this->logit("go_port_class", "init");
  }
}

go_port_class::~go_port_class () {
}

char const* go_port_class::object_name () {
  return "go_engine_class";
}

GoBaseClass* go_port_class::base_object () {
  return this->the_base_object;
}

void go_port_class::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void go_port_class::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

