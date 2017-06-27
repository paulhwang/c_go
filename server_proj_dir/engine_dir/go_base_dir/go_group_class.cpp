/*
  Copyrights reserved
  Written by Paul Hwang
  File name go_group_class.cpp
*/

#include <stdio.h>
#include "go_base_class.h"
#include "go_group_list_class.h"
#include "go_group_class.h"

GoGroupClass::GoGroupClass (GoGroupListClass *group_list_object_val):
    theGroupListObject(group_list_object_val),
    theStoneCount(0)
{
    this->debug(true, "GoGroupClass", "init");
}

int GoGroupClass::maxX (void)
{
    return this->theMaxX;
}

int GoGroupClass::minX (void)
{
    return this->theMinX;
}

int GoGroupClass::maxY (void)
{
    return this->theMaxY;
}

int GoGroupClass::minY (void)
{
    return this->theMinY;
}

void GoGroupClass::setMaxX (int val)
{
    this->theMaxX = val;
}

void GoGroupClass::setMinX (int val)
{
    this->theMinX = val;
}

void GoGroupClass::setMaxY (int val)
{
    this->theMaxY = val;
}

void GoGroupClass::setMinY (int val)
{
    this->theMinY = val;
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
    if (this->theExistMatrix[x_val][ y_val]) {
        this->abend("insertStoneToGroup", "stone already exists in group");
    }

    if (this->theStoneCount == 0) {
        this->theMaxX = x_val;
        this->theMinX = x_val;
        this->theMaxY = y_val;
        this->theMinY = y_val;
    } else {
        if (x_val > this->theMaxX) {
            this->theMaxX = x_val;
        }
        if (x_val < this->theMinX) {
            this->theMinX = x_val;
        }
        if (y_val > this->theMaxY) {
            this->theMaxY = y_val;
        }
        if (y_val < this->theMinY) {
            this->theMinY = y_val;
        }
    }

    this->theStoneCount++;
    this->theExistMatrix[x_val][y_val] = true;
    this->theDeadMatrix[x_val][y_val] = dead_val;
}

int isNeighborStone (int x1_val, int y1_val, int x2_val, int y2_val)
{
    if (x1_val == x2_val) {
        if ((y1_val + 1 == y2_val) || (y1_val - 1 == y2_val)) {
            return true;
        }
    }
    if (y1_val == y2_val) {
        if ((x1_val + 1 == x2_val) || (x1_val - 1 == x2_val)) {
            return true;
        }
    }
    return false;
}

int GoGroupClass::isCandidateGroup (int x_val, int y_val)
{
    int i = this->theMinX;
    while (i <= this->theMaxX) {
        int j = this->theMinY;
        while (j <= this->theMaxY) {
            if (this->theExistMatrix[i][j]) {
                //this.debug(false, "isCandidateGroup", "(" + x_val + "," + y_val + ") (" + i + "," + j + ")");
                if (isNeighborStone(i, j, x_val, y_val)) {
                    return true;
                }
            }
            j += 1;
        }
        i += 1;
    }
    return false;
}

int GoGroupClass::groupHasAir (void)
{
    int i = this->minX();
    while (i <= this->maxX()) {
        int j = this->minY();
        while (j <= this->maxY()) {
            if (this->theExistMatrix[i][j]) {
                if (this->theGroupListObject->fightObject()->baseObject()->boardObject()->stoneHasAir(i, j)) {
                    return true;
                }
            }
            j += 1;
        }
        i += 1;
    }
    return false;
}

void GoGroupClass::removeDeadStoneFromBoard (void)
{
    int i = this->theMinX;
    while (i <= this->theMaxX) {
        int j = this->theMinY;
        while (j <= this->theMaxY) {
            if (this->theExistMatrix[i][j]) {
                this->theGroupListObject->fightObject()->baseObject()->boardObject()->setBoardArray(i, j, GO_EMPTY_STONE);
                //this.debug(false, "removeDeadStoneFromBoard", "(" + i + "," + j + ")");
            }
            j += 1;
        }
        i += 1;
    }
}

void GoGroupClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseObject()->goBaseLogit(s, str1_val);
}

void GoGroupClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseObject()->goBaseAbend(s, str1_val);
}
