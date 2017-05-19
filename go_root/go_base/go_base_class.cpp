/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "../go_root_class.h"
#include "go_engine_class.h"
#include "go_board_class.h"
#include "go_port_class.h"
#include "go_config_class.h"
#include "go_base_class.h"
#include "go_game_class.h"

GoBaseClass::GoBaseClass (go_root_class* root_object_val) {
  this->theRootObject = root_object_val;
  this->theEngineObject = new GoEngineClass(this);
  this->theBoardObject = new GoBoardClass(this);
  this->thePortObject = new go_port_class(this);
  this->theConfigObject = new go_config_class(this);
  this->theGameObject = new go_game_class(this);

  if (1) {
    this->logit("GoBaseClass", "init");
  }
}

GoBaseClass::~GoBaseClass () {
}

char const* GoBaseClass::objectName () {
  return "GoBaseClass";
}

go_root_class* GoBaseClass::rootObject () {
  return this->theRootObject;
}

GoEngineClass* GoBaseClass::engineObject () {
  return this->theEngineObject;
}

GoBoardClass* GoBaseClass::boardObject () {
  return this->theBoardObject;
}

void GoBaseClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoBaseClass::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

