/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_board_class.cpp
*/

#include "../root_common.h"
#include "go_base_class.h"
#include "go_board_class.h"

GoBoardClass::GoBoardClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;
  /*
  this->theBoardArray = [19];
  this->theMarkedBoardArray = [19];
  int i = 0;
  while (i < 19) {
    this->theBoardArray[i] = [19];
    this->theMarkedBoardArray[i] = [19];
    i += 1;
  }
  */
  int i = 0;
  while (i < this->boardSize()) {
    int j = 0;
    while (j < this->boardSize()) {
      this->theBoardArray[i][j] = '0';
      this->theMarkedBoardArray[i][j] = '0';
      j += 1;
    }
    i += 1;
  }

  this->resetBoardObjectData();

  if (1) {
    this->logit("init", "");
  }
}

GoBoardClass::~GoBoardClass (void) {
}

char const* GoBoardClass::objectName (void) {
  return "GoBoardClass";
}

GoBaseClass* GoBoardClass::baseObject (void) {
  return this->theBaseObject;
}

GoConfigClass* GoBoardClass::configObject (void) {
  return this->baseObject()->configObject();
}

int GoBoardClass::boardSize (void) {
  return 19;
  //return this.configObject().boardSize();
};

void GoBoardClass::resetMarkedBoardObjectData (void) {

}

void GoBoardClass::encodeBoard (char* buf_ptr) {
  char *buf_ptr0 = buf_ptr;
  int i = 0;
  while (i < this->boardSize()) {
    int j = 0;
    while (j < this->boardSize()) {
      *buf_ptr0++ = this->theBoardArray[i][j];
      j += 1;
    }
    i += 1;
  }
  *buf_ptr0 = 0;

  if (0) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "data=%s", buf_ptr);
    this->logit("encodeBoard", s);
  }
}

void GoBoardClass::resetBoardObjectData (void) {

}

void GoBoardClass::logit (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseLogit(s, str1_val);
}

void GoBoardClass::abend (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseAbend(s, str1_val);
}

