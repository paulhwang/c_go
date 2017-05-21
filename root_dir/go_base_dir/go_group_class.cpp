/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "go_base_class.h"
#include "go_group_list_class.h"
#include "go_group_class.h"

GoGroupClass::GoGroupClass (GoGroupListClass* group_list_object_var) {
  this->theGroupListObject = group_list_object_var;

  if (1) {
    this->logit("GoGroupClass", "init");
  }
}

GoGroupClass::~GoGroupClass () {
}

char const* GoGroupClass::objectName () {
  return "GoGroupClass";
}

GoGroupListClass* GoGroupClass::groupListObject () {
  return this->theGroupListObject;
}

GoBaseClass* GoGroupClass::baseObject () {
  return this->groupListObject()->baseObject();
}

void GoGroupClass::logit (char const* str0_val, char const* str1_val) {
  this->baseObject()->logit(str0_val, str1_val);
}

void GoGroupClass::abend (char const* str0_val, char const* str1_val) {
  this->baseObject()->abend(str0_val, str1_val);
}
