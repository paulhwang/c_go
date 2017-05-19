/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "go_base_class.h"
#include "go_group_lst_class.h"

go_group_lst_class::go_group_lst_class (go_base_class* base_object_val) {
  this->the_base_object = base_object_val;

  if (1) {
    this->logit("go_group_lst_class", "init");
  }
}

go_group_lst_class::~go_group_lst_class () {
}

char const* go_group_lst_class::object_name () {
  return "go_group_lst_class";
}

go_base_class* go_group_lst_class::base_object () {
  return this->the_base_object;
}

void go_group_lst_class::logit (char const* str0_val, char const* str1_val) {
  LOGIT(str0_val, str1_val);
}

void go_group_lst_class::abend (char const* str0_val, char const* str1_val) {
  LOGIT(str0_val, str1_val);
}

