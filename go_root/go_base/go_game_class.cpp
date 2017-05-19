/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "go_base_class.h"
#include "go_game_class.h"

GoGameClass::GoGameClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;

  if (1) {
    this->logit("GoGameClass", "init");
  }
}

GoGameClass::~GoGameClass () {
}

char const* GoGameClass::objectName () {
  return "GoGameClass";
}

GoBaseClass* GoGameClass::baseObject () {
  return this->theBaseObject;
}

void GoGameClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoGameClass::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

