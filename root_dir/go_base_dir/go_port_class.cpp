/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_port_class.cpp
*/

#include "../root_common.h"
#include "go_base_class.h"
#include "go_port_class.h"

#define GO_PROTOCOL_CODE_SIZE 7
#define GO_PROTOCOL_CODE_PROPOSE      "Propose"
#define GO_PROTOCOL_CODE_ACCEPT       "Accept "
#define GO_PROTOCOL_CODE_CONFIRM      "Confirm"
#define GO_PROTOCOL_CODE_MOVE_DATA    "Move   "
#define GO_PROTOCOL_CODE_SPECIAL_MOVE "Special"
#define GO_PROTOCOL_CODE_BOARD_DATA   "Board  "

GoPortClass::GoPortClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;

  if (1) {
    this->logit("GoPortClass", "init");
  }
}

GoPortClass::~GoPortClass () {
}

char const* GoPortClass::objectName () {
  return "GoPortClass";
}

GoBaseClass* GoPortClass::baseObject () {
  return this->theBaseObject;
}

void GoPortClass::receiveStringData (char* str_val) {
  char code[GO_PROTOCOL_CODE_SIZE + 4];
  char data[32];

  this->logit("receiveStringData", str_val);

  if (!str_val) {
    this->abend("receiveStringData", "null input");
    return;
  }

  memcpy(code, str_val, GO_PROTOCOL_CODE_SIZE);
  memcpy(data, str_val + GO_PROTOCOL_CODE_SIZE, strlen(str_val) - GO_PROTOCOL_CODE_SIZE);
  this->logit("receiveStringData", code);
  this->logit("receiveStringData", data);

  if (strcmp(code, GO_PROTOCOL_CODE_MOVE_DATA)) {
    //this->aMoveIsPlayed(data);
    return;
  }

  if (strcmp(code, GO_PROTOCOL_CODE_SPECIAL_MOVE)) {
    //this->aSpecialMoveIsPlayed(data);
    return;
  }
};

void GoPortClass::logit (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseLogit(s, str1_val);
}

void GoPortClass::abend (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseAbend(s, str1_val);
}

