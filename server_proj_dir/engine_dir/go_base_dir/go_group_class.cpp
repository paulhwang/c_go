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
    theIndexNumber(theGroupListObject->groupCount()),
    theMyColor(theGroupListObject->myColor()),
    theStoneCount(0)
{
    this->theHisColor = (this->theMyColor == GO_EMPTY_STONE)
        ? GO_EMPTY_STONE
        : GolbalGoGetOppositeColor(this->theMyColor);
    this->debug(true, "GoGroupClass", "init");
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

void GoGroupClass::mergeWithOtherGroup (GoGroupClass *group2)
{
    this->debug(false, "mergeWithOtherGroup", "");
    int i = group2->theMinX;
    while (i <= group2->theMaxX) {
        int j = group2->theMinY;
        while (j <= group2->theMaxY) {
            if (group2->theExistMatrix[i][j]) {
                //this.debug(false, "mergeWithOtherGroup", "i=" + i + " j=" + j);
                if (this->theExistMatrix[i][j]) {
                    this->abend("mergeWithOtherGroup", "already exist");
                }
                this->theExistMatrix[i][j] = group2->theExistMatrix[i][j];
                this->theStoneCount++;

                group2->theExistMatrix[i][j] = 0;
                group2->theStoneCount--;
            }
            j += 1;
        }
        i += 1;
    }
    if (group2->theStoneCount) {
        this->abend("mergeWithOtherGroup", "theStoneCount");
    }

    if (this->theMaxX < group2->theMaxX) {
        this->theMaxX = group2->theMaxX;
    }
    if (this->theMinX > group2->theMinX) {
        this->theMinX = group2->theMinX;
    }
    if (this->theMaxY < group2->theMaxY) {
        this->theMaxY = group2->theMaxY;
    }
    if (this->theMinY > group2->theMinY) {
        this->theMinY = group2->theMinY;
    }

    if (group2->theGroupListObject->groupArray(group2->theIndexNumber) != group2) {
        this->abend("mergeWithOtherGroup", "group2");
    }
}

int GoGroupClass::groupHasAir (void)
{
    int i = this->theMinX;
    while (i <= this->theMaxX) {
        int j = this->theMinY;
        while (j <= this->theMaxY) {
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

void GoGroupClass::abendGroup (void)
{
    int count = 0;
    int board_size = this->theGroupListObject->fightObject()->baseObject()->configObject()->boardSize();
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (this->theExistMatrix[i][j]) {
                 count++;
            }
        }
    }
    if (this->theStoneCount != count) {
        this->abend("abendGroup", "stone count");
    }
}

void GoGroupClass::abendOnGroupConflict (GoGroupClass *other_group_val)
{
   int board_size = this->theGroupListObject->fightObject()->baseObject()->configObject()->boardSize();
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (this->theExistMatrix[i][j]) {
                if (other_group_val->theExistMatrix[i][j]) {
                    this->abend("abendOnGroupConflict", "stone  exists in 2 groups");
                    //this->abend("abendOnGroupConflict", "stone (" + i + "," + j + ") exists in 2 groups: (" + this.myColor() + ":" + this.indexNumber() + ":" + this.stoneCount() + ") ("
                    //    + other_group_val.myColor() + ":" + other_group_val.indexNumber() + ":" + other_group_val.stoneCount() + ")");
                }
            }
        }
    }
}

void GoGroupClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theGroupListObject->fightObject()->baseObject()->goBaseLogit(s, str1_val);
}

void GoGroupClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theGroupListObject->fightObject()->baseObject()->goBaseAbend(s, str1_val);
}
