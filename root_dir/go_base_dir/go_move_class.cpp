/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_move_class.cpp
*/

#include "../root_common.h"
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

char const* GoMoveClass::objectName () {
  return "GoMoveClass";
}

GoBaseClass* GoMoveClass::baseObject () {
  return this->theBaseObject;
}

void GoMoveClass::logit (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseLogit(s, str1_val);
}

void GoMoveClass::abend (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseAbend(s, str1_val);
}



