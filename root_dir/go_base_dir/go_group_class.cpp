/*
  Copyrights reserved
  Written by Paul Hwang
  File name go_group_class.cpp
*/

#include "../root_common.h"
#include "go_base_class.h"
#include "go_group_list_class.h"
#include "go_group_class.h"

GoGroupClass::GoGroupClass (GoGroupListClass* group_list_object_var) {
  this->theGroupListObject = group_list_object_var;

  if (1) {
    this->logit("GoGroupClass", "init");
  }
}

GoGroupClass::~GoGroupClass () {
}

char const* GoGroupClass::objectName () {
  return "GoGroupClass";
}

GoGroupListClass* GoGroupClass::groupListObject () {
  return this->theGroupListObject;
}

GoBaseClass* GoGroupClass::baseObject () {
  return this->groupListObject()->baseObject();
}

int isCandidateGroup (int x_val, int y_val)
{
  /*
        this.debug(false, "isCandidateGroup", "(" + x_val + "," + y_val + ")");
        var i, j;
        i = this.minX();
        while (i <=  this.maxX()) {
            j = this.minY();
            while (j <=  this.maxY()) {
                if (this.existMatrix(i, j)) {
                    this.debug(false, "isCandidateGroup", "(" + x_val + "," + y_val + ") (" + i + "," + j + ")");
                    if (this.GO().isNeighborStone(i, j, x_val, y_val)) {
                        return true;
                    }
                }
                j += 1;
            }
            i += 1;
        }
        */
    return false;
}

void GoGroupClass::logit (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseLogit(s, str1_val);
}

void GoGroupClass::abend (char const* str0_val, char const* str1_val) {
  char s[LOGIT_BUF_SIZE];
  sprintf(s, "%s::%s", this->objectName(), str0_val);
  this->baseObject()->goBaseAbend(s, str1_val);
}

