/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_group_list_class.cpp
*/

#include "../root_common.h"
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

GoGroupClass* GoGroupListClass::findCandidateGroup (int x_val, int y_val)
{
    int i = 0;
    //while (i < this->groupCount()) {
        //if (this->listArray(i)->isCandidateGroup(x_val, y_val)) {
        //    return this.listArray(i);
        //}
        i += 1;
    //}
    return 0;
}

void GoGroupListClass::logit (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseLogit(s, str1_val);
}

void GoGroupListClass::abend (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseAbend(s, str1_val);
}

