/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "go_base_class.h"
#include "go_group_class.h"

GoGroupClass::GoGroupClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;

  if (1) {
    this->logit("GoGroupClass", "init");
  }
}

GoGroupClass::~GoGroupClass () {
}

char const* GoGroupClass::objectName () {
  return "GoGroupClass";
}

GoBaseClass* GoGroupClass::baseObject () {
  return this->theBaseObject;
}

void GoGroupClass::resetMarkedBoardObjectData () {

}

void GoGroupClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoGroupClass::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

