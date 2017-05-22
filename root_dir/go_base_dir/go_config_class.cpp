/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_config_class.cpp
*/

#include "../root_common.h"
#include "go_base_class.h"
#include "go_config_class.h"

GoConfigClass::GoConfigClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;
  this->theBoardSize = 19;//////////////////////

  if (1) {
    this->logit("GoConfigClass", "init");
  }
}

GoConfigClass::~GoConfigClass (void) {
}

char const* GoConfigClass::objectName (void) {
  return "GoConfigClass";
}

GoBaseClass* GoConfigClass::baseObject (void) {
  return this->theBaseObject;
}

int GoConfigClass::boardSize (void) {
  return this->theBoardSize;
};

int GoConfigClass::isValidCoordinates (int x_val, int y_val)
{
    return this->isValidCoordinate(x_val) && this->isValidCoordinate(y_val) ;
}

int GoConfigClass::isValidCoordinate (int coordinate_val)
{
    return (0 <= coordinate_val) && (coordinate_val < this->boardSize());
}

void GoConfigClass::logit (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseLogit(s, str1_val);
}

void GoConfigClass::abend (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseAbend(s, str1_val);
}

