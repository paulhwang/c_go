/*
  Copyrights reserved
  Written by Paul Hwang
  File name: root_class.cpp
*/

#include "../utils_dir/logit.h"
#include "base_mgr_dir/base_mgr_class.h"
#include "go_base_dir/go_base_class.h"
#include "../utils_dir/transport_class.h"
#include "root_class.h"

GoRootClass::GoRootClass () {
  this->theBaseMgrObject = new BaseMgrClass(this);
  this->theGoBaseObject = new GoBaseClass(this);
  this->theTransportObject = new TransportClass(this);

  if (1) {
  	this->logit("GoRootClass", "init");
  }
}

GoRootClass::~GoRootClass () {
}

BaseMgrClass* GoRootClass::baseMgrObject() {
  return this->theBaseMgrObject;
}

GoBaseClass* GoRootClass::goBaseObject() {
  return this->theGoBaseObject;
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


