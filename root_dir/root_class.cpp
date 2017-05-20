/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../utils_dir/logit.h"
#include "go_base_dir/go_base_class.h"
#include "../utils_dir/transport_class.h"
#include "root_class.h"

GoRootClass::GoRootClass () {
  this->theBaseObject = new GoBaseClass(this);
  this->theTransportObject = new TransportClass(this);

  if (1) {
  	this->logit("GoRootClass", "init");
  }
}

GoRootClass::~GoRootClass () {
}

GoBaseClass* GoRootClass::baseObject() {
  return this->theBaseObject;
}

TransportClass* GoRootClass::transportObject() {
  return this->theTransportObject;
}

char const* GoRootClass::objectName () {
  return "GoRootClass";
}

void GoRootClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoRootClass::abend (char const* str0_val, char const* str1_val) {
	ABEND(str0_val, str1_val);
}


