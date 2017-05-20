/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "go_base_class.h"
#include "go_group_list_class.h"

GoGroupListClass::GoGroupListClass (GoEngineClass* engine_val,
                                    int index_val,
                                    int color_val,
                                    int dead_val,
                                    char const* big_stone_val,
                                    char const* small_stone_val) {
  this->theEngineObject = engine_val;

  if (1) {
    this->logit("GoGroupListClass", "init");
  }
}

GoGroupListClass::~GoGroupListClass () {
}

char const* GoGroupListClass::objectName () {
  return "GoGroupListClass";
}

GoEngineClass* GoGroupListClass::engineObject () {
  return this->theEngineObject;
}

GoBaseClass* GoGroupListClass::baseObject () {
  return this->engineObject()->baseObject();
}

void GoGroupListClass::logit (char const* str0_val, char const* str1_val) {
  this->baseObject()->logit(str0_val, str1_val);
}

void GoGroupListClass::abend (char const* str0_val, char const* str1_val) {
  this->baseObject()->abend(str0_val, str1_val);
}

