/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_board_class.cpp
*/

#include "../root_common.h"
#include "go_base_class.h"
#include "go_board_class.h"

GoBoardClass::GoBoardClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;

  if (1) {
    this->logit("init", "");
  }
}

GoBoardClass::~GoBoardClass () {
}

char const* GoBoardClass::objectName () {
  return "GoBoardClass";
}

GoBaseClass* GoBoardClass::baseObject () {
  return this->theBaseObject;
}

void GoBoardClass::resetMarkedBoardObjectData () {

}

void GoBoardClass::logit (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseLogit(s, str1_val);
}

void GoBoardClass::abend (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseAbend(s, str1_val);
}

