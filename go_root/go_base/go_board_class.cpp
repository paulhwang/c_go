/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "go_base_class.h"
#include "go_board_class.h"

GoBoardClass::GoBoardClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;

  if (1) {
    this->logit("GoBoardClass", "init");
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
  this->baseObject()->logit(str0_val, str1_val);
}

void GoBoardClass::abend (char const* str0_val, char const* str1_val) {
  this->baseObject()->abend(str0_val, str1_val);
}

