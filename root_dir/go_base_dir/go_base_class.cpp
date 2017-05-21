/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.cpp
*/

#include "../../utils_dir/logit.h"
#include "../root_class.h"
#include "go_base_class.h"

GoBaseClass::GoBaseClass (GoRootClass* root_object_val) {
  this->theRootObject = root_object_val;
  this->theBoardObject = new GoBoardClass(this);
  this->theEngineObject = new GoEngineClass(this);
  this->thePortObject = new GoPortClass(this);
  this->theConfigObject = new GoConfigClass(this);
  this->theGameObject = new GoGameClass(this);
  GoMoveClass* m = new GoMoveClass(this);

  if (1) {
    this->logit("GoBaseClass", "init");
  }
}

GoBaseClass::~GoBaseClass () {
}

char const* GoBaseClass::objectName () {
  return "GoBaseClass";
}

GoRootClass* GoBaseClass::rootObject () {
  return this->theRootObject;
}

GoEngineClass* GoBaseClass::engineObject () {
  return this->theEngineObject;
}

GoBoardClass* GoBaseClass::boardObject () {
  return this->theBoardObject;
}

GoPortClass* GoBaseClass::portObject () {
  return this->thePortObject;
}

void GoBaseClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoBaseClass::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

