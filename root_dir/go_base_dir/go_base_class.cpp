/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.cpp
*/

#include "../root_common.h"
#include "../../utils_dir/logit.h"
#include "../base_mgr_dir/base_mgr_class.h"
#include "go_base_class.h"

GoBaseClass::GoBaseClass (BaseMgrClass* base_mgr_object_val) {
  this->theBaseMgrObject = base_mgr_object_val;
  this->theConfigObject = new GoConfigClass(this);
  this->theBoardObject = new GoBoardClass(this);
  this->theEngineObject = new GoEngineClass(this);
  this->thePortObject = new GoPortClass(this);
  this->theGameObject = new GoGameClass(this);

  this->portObject()->receiveStringData("Move   03031001");

  if (1) {
    this->logit("GoBaseClass", "init");
  }
}

GoBaseClass::~GoBaseClass (void) {
}

char const* GoBaseClass::objectName (void) {
  return "GoBaseClass";
}

BaseMgrClass* GoBaseClass::baseMgrObject (void) {
  return this->theBaseMgrObject;
}

GoEngineClass* GoBaseClass::engineObject (void) {
  return this->theEngineObject;
}

GoBoardClass* GoBaseClass::boardObject (void) {
  return this->theBoardObject;
}

GoPortClass* GoBaseClass::portObject (void) {
  return this->thePortObject;
}

GoGameClass* GoBaseClass::gameObject (void) {
  return this->theGameObject;
}

GoConfigClass* GoBaseClass::configObject (void) {
  return this->theConfigObject;
}

void GoBaseClass::goBaseLogit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoBaseClass::goBaseAbend (char const* str0_val, char const* str1_val) {
	ABEND(str0_val, str1_val);
}

void GoBaseClass::logit (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->goBaseLogit(s, str1_val);
}

void GoBaseClass::abend (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->goBaseAbend(s, str1_val);
}


