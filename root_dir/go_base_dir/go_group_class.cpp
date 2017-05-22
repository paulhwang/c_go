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

GoGroupClass::~GoGroupClass (void)
{
}

char const* GoGroupClass::objectName (void)
{
  return "GoGroupClass";
}

GoGroupListClass* GoGroupClass::groupListObject (void)
{
    return this->theGroupListObject;
}

void GoGroupClass::setGroupListObject (GoGroupListClass* group_list_val)
{
    this->theGroupListObject = group_list_val;
}

GoBaseClass* GoGroupClass::baseObject (void)
{
    return this->groupListObject()->baseObject();
}

int GoGroupClass::indexNumber (void)
{
    return this->theIndexNumber;
}

void GoGroupClass::setIndexNumber (int val)
{
    this->theIndexNumber = val;
}

void GoGroupClass::insertStoneToGroup (int x_val, int y_val, int dead_val)
{
  /*
        this.debug(false, "insertStoneToGroup", "(" + x_val + "," + y_val + "," + this.myColor() + ")");
        if (this.existMatrix(x_val, y_val)) {
            this.abend("insertStoneToGroup", "stone (" + x_val + "," + y_val + "," + this.myColor() + ") already exists in group");
        }

        if (this.stoneCount() == 0) {
            this.setMaxX(x_val);
            this.setMinX(x_val);
            this.setMaxY(y_val);
            this.setMinY(y_val);
        } else {
            if (x_val > this.maxX()) {
                this.setMaxX(x_val);
            }
            if (x_val < this.minX()) {
                this.setMinX(x_val);
            }
            if (y_val > this.maxY()) {
                this.setMaxY(y_val);
            }
            if (y_val < this.minY()) {
                this.setMinY(y_val);
            }
        }

        this.incrementStoneCount();
        this.setExistMatrix(x_val, y_val, true);
        this.setDeadMatrix(x_val, y_val, dead_val);
        */
}

int GoGroupClass::isCandidateGroup (int x_val, int y_val)
{
    int i, j;

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "(%i, %i)", x_val, y_val);
        this->logit("isCandidateGroup", s);
    }

  /*
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

