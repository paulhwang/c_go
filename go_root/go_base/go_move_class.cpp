/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "go_move_class.h"

go_move_class::go_move_class () {

}

go_move_class::~go_move_class () {


}

void go_move_class::debug (int debug_val, char const* str0_val, char const* str1_val) {
  if (debug_val) {
    LOGIT(str0_val, str1_val);
  }
}

void go_move_class::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

