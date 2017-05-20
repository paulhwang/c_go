/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "go_base_class.h"
#include "go_config_class.h"

GoConfigClass::GoConfigClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;

  if (1) {
    this->logit("GoConfigClass", "init");
  }
}

GoConfigClass::~GoConfigClass () {
}

char const* GoConfigClass::objectName () {
  return "GoConfigClass";
}

GoBaseClass* GoConfigClass::baseObject () {
  return this->theBaseObject;
}

void GoConfigClass::logit (char const* str0_val, char const* str1_val) {
  this->baseObject()->logit(str0_val, str1_val);
}

void GoConfigClass::abend (char const* str0_val, char const* str1_val) {
  this->baseObject()->abend(str0_val, str1_val);
}

