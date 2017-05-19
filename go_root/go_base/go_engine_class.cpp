/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../utils/logit.h"
#include "go_base_class.h"
#include "go_engine_class.h"

GoEngineClass::GoEngineClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;
  this->resetEngineObjectData();

  if (1) {
    this->logit("GoEngineClass", "init");
  }
}

GoEngineClass::~GoEngineClass () {
}

char const* GoEngineClass::objectName () {
  return "GoEngineClass";
}

GoBaseClass* GoEngineClass::baseObject () {
  return this->theBaseObject;
}

void GoEngineClass::resetEngineObjectData () {
  this->theGroupListCount = 7;
        //this.theGroupListArray = [this.groupListCount()];
        //this.theGroupListArray[1] = this.mallocGroupList(this, 1, this.GO().BLACK_STONE(), false, null, null);
        //this.theGroupListArray[2] = this.mallocGroupList(this, 2, this.GO().WHITE_STONE(), false, null, null);
        //this.resetMarkedGroupLists();
        //this.resetEmptyGroupLists();

        //this.theCaptureCount = null;
        //this.theLastDeadStone = null;

  this->theBlackCaptureStones = 0;
  this->theWhiteCaptureStones = 0;
}

void GoEngineClass::logit (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

void GoEngineClass::abend (char const* str0_val, char const* str1_val) {
	LOGIT(str0_val, str1_val);
}

