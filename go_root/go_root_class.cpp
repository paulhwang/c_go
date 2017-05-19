/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../utils/logit.h"
#include "./go_base/go_base_class.h"
#include "./go_root_class.h"

go_root_class::go_root_class () {
  this->the_base_object = new go_base_class(this);

  if (1) {
  	this->logit("go_root_class", "init");
  }
}

go_root_class::~go_root_class () {
}

go_base_class* go_root_class::base_object() {
	return this->the_base_object;
}

char const* go_root_class::object_name () {
  return "go_root_class";
}

void go_root_class::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void go_root_class::abend (char const* str0_val, char const* str1_val) {
	ABEND(str0_val, str1_val);
}


