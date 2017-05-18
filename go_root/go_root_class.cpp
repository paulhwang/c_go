/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "go_root_class.h"
#include "./go_base/go_base_class.h"

go_root_class::go_root_class () {
  go_base_class* base_object = new go_base_class();
  this->debug(TRUE, "go_root_class", "init");
}

go_root_class::~go_root_class () {


}

void go_root_class::debug (int debug_val, char const* str0_val, char const* str1_val) {
  if (debug_val) {
    LOGIT(str0_val, str1_val);
  }
}

void go_root_class::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}


