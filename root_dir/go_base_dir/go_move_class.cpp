/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "go_base_class.h"
#include "go_move_class.h"

GoMoveClass::GoMoveClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;

  if (1) {
    this->logit("GoMoveClass", "init");
  }
}

GoMoveClass::~GoMoveClass () {
}

GoBaseClass* GoMoveClass::baseObject () {
  return this->theBaseObject;
}

void GoMoveClass::logit (char const* str0_val, char const* str1_val) {
	this->baseObject()->logit(str0_val, str1_val);
}

void GoMoveClass::abend (char const* str0_val, char const* str1_val) {
	this->baseObject()->abend(str0_val, str1_val);
}



