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
        : getOppositeColor(this->theMyColor);

    this->debug(true, "GoGroupListClass", "init");
}

int GoGroupListClass::totalStoneCount (void)
{
    int count = 0;
    int i = 0;
    while (i < this->theGroupCount) {
        count += this->theListArray[i]->theStoneCount;
        i += 1;
    }
    return count;
}

void GoGroupListClass::insertGroupToGroupList (GoGroupClass* group_val)
{
    this->theListArray[this->theGroupCount] = group_val;
    group_val->setIndexNumber(this->theGroupCount);
    this->theGroupCount++;
    group_val->setGroupListObject(this);
}

GoGroupClass *GoGroupListClass::findCandidateGroup (int x_val, int y_val)
{
    int i = 0;
    while (i < this->theGroupCount) {
        if (this->theListArray[i]->isCandidateGroup(x_val, y_val)) {
            return this->theListArray[i];
        }
        i += 1;
    }
    return 0;
}

void GoGroupListClass::removeGroupFromGroupList (GoGroupClass *group_val)
{
    this->theGroupCount;

    if (group_val->theIndexNumber != this->theGroupCount) {
        this->theListArray[this->theGroupCount]->setIndexNumber(group_val->theIndexNumber);
        this->theListArray[group_val->theIndexNumber] = this->theListArray[this->theGroupCount];
    }

    this->theListArray[this->theGroupCount] = 0;
}

void GoGroupListClass::abendGroupList (void)
{

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
