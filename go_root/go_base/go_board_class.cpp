/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "go_base_class.h"
#include "go_board_class.h"

go_board_class::go_board_class (GoBaseClass* base_object_val) {
  this->the_base_object = base_object_val;

  if (1) {
    this->logit("go_board_class", "init");
  }
}

go_board_class::~go_board_class () {
}

char const* go_board_class::object_name () {
  return "go_board_class";
}

GoBaseClass* go_board_class::base_object () {
  return this->the_base_object;
}

void go_board_class::resetMarkedBoardObjectData () {

}

void go_board_class::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void go_board_class::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

