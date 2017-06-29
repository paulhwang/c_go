/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_group_list_class.cpp
*/

#include <stdio.h>
#include "go_base_class.h"
#include "go_group_list_class.h"

GoGroupListClass::GoGroupListClass (GoFightClass* fight_object_val,
                                    int index_val,
                                    int color_val,
                                    int dead_val,
                                    char const *big_stone_val,
                                    char const *small_stone_val):
    theFightObject(fight_object_val),
    theIndexNumber(index_val),
    theMyColor(color_val),
    theIsDead(dead_val),
    theBigStoneColor(big_stone_val),
    theSmallStoneColor(small_stone_val),
    theGroupCount(0),
    theIsMarkedDead(0)
{
    this->theHisColor = (this->theMyColor == GO_EMPTY_STONE)
        ? GO_EMPTY_STONE
        : GolbalGoGetOppositeColor(this->theMyColor);

    this->debug(true, "GoGroupListClass", "init");
}

int GoGroupListClass::totalStoneCount (void)
{
    int count = 0;
    int i = 0;
    while (i < this->theGroupCount) {
        count += this->theGroupArray[i]->theStoneCount;
        i += 1;
    }
    return count;
}

void GoGroupListClass::insertGroupToGroupList (GoGroupClass* group_val)
{
    this->theGroupArray[this->theGroupCount] = group_val;
    group_val->setIndexNumber(this->theGroupCount);
    this->theGroupCount++;
    group_val->setGroupListObject(this);
}

GoGroupClass *GoGroupListClass::findCandidateGroup (int x_val, int y_val)
{
    int i = 0;
    while (i < this->theGroupCount) {
        if (this->theGroupArray[i]->isCandidateGroup(x_val, y_val)) {
            return this->theGroupArray[i];
        }
        i += 1;
    }
    return 0;
}

GoGroupClass *GoGroupListClass::findOtherCandidateGroup (GoGroupClass *group_val, int x_val, int y_val)
{
    int i = 0;
    while (i < this->theGroupCount) {
        if (this->theGroupArray[i] != group_val) {
            if (this->theGroupArray[i]->isCandidateGroup(x_val, y_val)) {
                return this->theGroupArray[i];
            }
        }
        i += 1;
    }
    return 0;
}

void GoGroupListClass::removeGroupFromGroupList (GoGroupClass *group_val)
{
    this->theGroupCount--;
    if (group_val->theIndexNumber != this->theGroupCount) {
        this->theGroupArray[this->theGroupCount]->setIndexNumber(group_val->theIndexNumber);
        this->theGroupArray[group_val->theIndexNumber] = this->theGroupArray[this->theGroupCount];
    }
    this->theGroupArray[this->theGroupCount] = 0;
}

int GoGroupListClass::stoneExistWithinMe (int x_val, int y_val)
{
    int i = 0;
    while (i < this->theGroupCount) {
        GoGroupClass *group = this->theGroupArray[i];
        if (group->theExistMatrix[x_val][y_val]) {
            return true;
        }
        i += 1;
    }
    return false;
}

void GoGroupListClass::abendGroupList (void)
{
    /*
        var d;
        if (this.isDead()) {
            d = "d* ";
        } else {
            d = "*";
        }

        this.debug(false, "abendGroupList", "" + this.indexNumber() + " color=" + this.myColor() + " count=" + this.groupCount() + ":" + this.totalStoneCount());
 */
    int i = 0;
    while (i < this->theGroupCount) {
        GoGroupClass *group = this->theGroupArray[i];
         if (!group) {
            this->abend("abendGroupList", "null group" );
            return;
        }
        if (group->theGroupListObject != this) {
            this->abend("abendGroupList", "groupListObject");
            return;
        }
        if (group->theIndexNumber != i) {
            this->abend("abendGroupList", "index ");
            return;
        }

        group->abendGroup();

        int j = i + 1;
        while (j < this->theGroupCount) {
            group->abendOnGroupConflict(this->theGroupArray[j]);
            j = j + 1;
        }
        i += 1;
    }

}

void GoGroupListClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theFightObject->baseObject()->goBaseLogit(s, str1_val);
}

void GoGroupListClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theFightObject->baseObject()->goBaseAbend(s, str1_val);
}
