/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "go_base_class.h"

go_base_class::go_base_class () {
  this->debug(TRUE, "go_base_class", "init");
}

go_base_class::~go_base_class () {

}

void go_base_class::debug (int debug_val, char const* str0_val, char const* str1_val) {
  if (debug_val) {
    LOGIT(str0_val, str1_val);
  }
}

void go_base_class::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

