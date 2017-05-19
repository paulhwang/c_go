/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../utils/logit.h"
#include "./go_base/go_base_class.h"
#include "./go_root_class.h"

goRootClass::goRootClass () {
  this->the_base_object = new GoBaseClass(this);

  if (1) {
  	this->logit("goRootClass", "init");
  }
}

goRootClass::~goRootClass () {
}

GoBaseClass* goRootClass::base_object() {
	return this->the_base_object;
}

char const* goRootClass::object_name () {
  return "goRootClass";
}

void goRootClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void goRootClass::abend (char const* str0_val, char const* str1_val) {
	ABEND(str0_val, str1_val);
}


