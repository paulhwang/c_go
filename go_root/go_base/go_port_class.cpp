/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "go_base_class.h"
#include "go_port_class.h"

GoPortClass::GoPortClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;

  if (1) {
    this->logit("GoPortClass", "init");
  }
}

GoPortClass::~GoPortClass () {
}

char const* GoPortClass::objectName () {
  return "GoPortClass";
}

GoBaseClass* GoPortClass::baseObject () {
  return this->theBaseObject;
}

void GoPortClass::logit (char const* str0_val, char const* str1_val) {
  this->baseObject()->logit(str0_val, str1_val);
}

void GoPortClass::abend (char const* str0_val, char const* str1_val) {
  this->baseObject()->abend(str0_val, str1_val);
}

