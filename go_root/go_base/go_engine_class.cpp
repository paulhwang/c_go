/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "../../includes/types.h"
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

GoBoardClass* GoEngineClass::boardObject () {
  return this->baseObject()->boardObject();
}

void GoEngineClass::resetMarkedGroupLists () {
  this->theGroupListArray[3] = new GoGroupListClass(this, 3, GO_BLACK_STONE, true, "black", "gray");
  this->theGroupListArray[4] = new GoGroupListClass(this, 4, GO_WHITE_STONE, true, "white", "gray");
  this->boardObject()->resetMarkedBoardObjectData();
}

void GoEngineClass::resetEmptyGroupLists () {
  this->theGroupListArray[0] = new GoGroupListClass(this, 0, GO_EMPTY_STONE, false, null, null);
  this->theGroupListArray[5] = new GoGroupListClass(this, 5, GO_EMPTY_STONE, false, null, "black");
  this->theGroupListArray[6] = new GoGroupListClass(this, 6, GO_EMPTY_STONE, false, null, "white");
}

void GoEngineClass::resetEngineObjectData () {
  this->theGroupListCount = GO_GROUP_LIST_ARRAY_SIZE;
  //this.theGroupListArray = [this.groupListCount()];
  this->theGroupListArray[1] = new GoGroupListClass(this, 1, GO_BLACK_STONE, false, null, null);
  this->theGroupListArray[2] = new GoGroupListClass(this, 2, GO_WHITE_STONE, false, null, null);
  this->resetMarkedGroupLists();
  this->resetEmptyGroupLists();

  this->theCaptureCount = null;
  this->theLastDeadStone = null;

  this->theBlackCaptureStones = 0;
  this->theWhiteCaptureStones = 0;
}

void GoEngineClass::logit (char const* str0_val, char const* str1_val) {
	this->baseObject()->logit(str0_val, str1_val);
}

void GoEngineClass::abend (char const* str0_val, char const* str1_val) {
	this->baseObject()->abend(str0_val, str1_val);
}

