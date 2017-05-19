/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "go_base_class.h"
#include "go_port_class.h"

GoPortClass::GoPortClass (GoBaseClass* base_object_val) {
  this->the_base_object = base_object_val;

  if (1) {
    this->logit("GoPortClass", "init");
  }
}

GoPortClass::~GoPortClass () {
}

char const* GoPortClass::object_name () {
  return "go_engine_class";
}

GoBaseClass* GoPortClass::base_object () {
  return this->the_base_object;
}

void GoPortClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoPortClass::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

