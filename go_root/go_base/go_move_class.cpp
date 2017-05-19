/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "go_move_class.h"
#include "../../utils/logit.h"

go_move_class::go_move_class () {

}

go_move_class::~go_move_class () {
}

void go_move_class::logit (char const* str0_val, char const* str1_val) {
  LOGIT(str0_val, str1_val);
}


void go_move_class::abend (char const* str0_val, char const* str1_val) {
  ABEND(str0_val, str1_val);
}

