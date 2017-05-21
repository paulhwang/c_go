/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_class.cpp
*/

#include "../../utils_dir/logit.h"
#include "../root_class.h"
#include "base_class.h"

BaseClass::BaseClass (BaseMgrClass* base_mgr_object_val)) {
  this->theBaseMgrObject = root_object_val;

  if (1) {
    this->logit("BaseClass", "init");
  }
}

BaseClass::~BaseClass () {
}

char const* BaseClass::BaseClass () {
  return "BaseClass";
}

BaseMgrClass* BaseClass::baseMgrObject () {
  return this->theBaseMgrObject;
}

void BaseClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoRootClass::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

