/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_class.cpp
*/

#include "../../utils_dir/logit.h"
#include "../root_class.h"
#include "base_mgr_class.h"

BaseMgrClass::BaseMgrClass (RootClass* root_object_val) {
  this->theRootObject = root_object_val;

  if (1) {
    this->logit("BaseMgrClass", "init");
  }
}

BaseMgrClass::~BaseMgrClass () {
}

char const* BaseMgrClass::objectName () {
  return "BaseMgrClass";
}

RootClass* BaseMgrClass::rootObject () {
  return this->theRootObject;
}

void BaseMgrClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void BaseMgrClass::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

