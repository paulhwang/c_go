/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "go_base_class.h"
#include "go_board_class.h"

GoBoardClass::GoBoardClass (GoBaseClass* base_object_val) {
  this->the_base_object = base_object_val;

  if (1) {
    this->logit("GoBoardClass", "init");
  }
}

GoBoardClass::~GoBoardClass () {
}

char const* GoBoardClass::object_name () {
  return "GoBoardClass";
}

GoBaseClass* GoBoardClass::base_object () {
  return this->the_base_object;
}

void GoBoardClass::resetMarkedBoardObjectData () {

}

void GoBoardClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoBoardClass::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

