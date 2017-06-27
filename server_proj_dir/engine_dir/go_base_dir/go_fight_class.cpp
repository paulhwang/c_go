/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_figth_class.cpp
*/

#include <stdio.h>
#include "go_base_class.h"
#include "go_fight_class.h"

GoFightClass::GoFightClass (GoBaseClass* base_object_val):
    theBaseObject(base_object_val)
{
    this->resetEngineObjectData();
    this->debug(true, "GoFightClass", "init");
}

void GoFightClass::enterBattle (GoMoveClass* move_val)
{
     this->debug(true, "enterBattle", move_val->moveInfo());

    GoGroupClass* group = this->insertStoneToGroupList(move_val);
    if (!group) {
        return;
    }

    this->theBaseObject->boardObject()->addStoneToBoard(move_val->xX(), move_val->yY(), move_val->myColor());
    int dead_count = this->killOtherColorGroups(move_val, group);

    if (!group->groupHasAir()) {
    //    this->removeDeadGroup(group);
    }

    if (dead_count != 0) {
        if (move_val->myColor() == GO_BLACK_STONE) {
            //this->addBlackCaptureStones(dead_count);
        } else if (move_val->myColor() == GO_WHITE_STONE) {
            //this->addWhiteCaptureStones(dead_count);
        } else {
            this->abend("enterBattle", "bad color=");
        }
    }
    this->abendEngine();
}

GoGroupClass* GoFightClass::insertStoneToGroupList (GoMoveClass* move_val)
{
    GoGroupListClass* g_list;

    if (move_val->myColor() == GO_BLACK_STONE) {
        g_list = this->blackGroupList();
    }
    else if (move_val->myColor() == GO_WHITE_STONE) {
        g_list = this->whiteGroupList();
    } else {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "move_val: (%i, %i, %i, %i)", move_val->xX(), move_val->yY(), move_val->myColor(), move_val->turnIndex());
        this->abend("insertStoneToGroupList", s);
        return 0;
    }

    GoGroupClass* group = g_list->findCandidateGroup(move_val->xX(), move_val->yY());
    if (!group) {
        group = new GoGroupClass(g_list);
        group->insertStoneToGroup(move_val->xX(), move_val->yY(), false);
        g_list->insertGroupToGroupList(group);
        //g_list.printGroupList();
        return group;
    }

}

int GoFightClass::killOtherColorGroups(GoMoveClass* move_val, GoGroupClass* group_val)
{
    this->theLastDeadStone = 0;

    int count;
    count = this->killOtherColorGroup(group_val, move_val->xX() - 1, move_val->yY());
    count += this->killOtherColorGroup(group_val, move_val->xX() + 1, move_val->yY());
    count += this->killOtherColorGroup(group_val, move_val->xX(), move_val->yY() - 1);
    count += this->killOtherColorGroup(group_val, move_val->xX(), move_val->yY() + 1);
    return count;
}

int GoFightClass::killOtherColorGroup(GoGroupClass* group, int x_val, int y_val)
{
    return 0;
}

void GoFightClass::resetMarkedGroupLists (void)
{
    this->theGroupListArray[3] = new GoGroupListClass(this, 3, GO_BLACK_STONE, true, "black", "gray");
    this->theGroupListArray[4] = new GoGroupListClass(this, 4, GO_WHITE_STONE, true, "white", "gray");
    this->theBaseObject->boardObject()->resetMarkedBoardObjectData();
}

void GoFightClass::resetEmptyGroupLists (void)
{
    this->theGroupListArray[0] = new GoGroupListClass(this, 0, GO_EMPTY_STONE, false, 0, 0);
    this->theGroupListArray[5] = new GoGroupListClass(this, 5, GO_EMPTY_STONE, false, 0, "black");
    this->theGroupListArray[6] = new GoGroupListClass(this, 6, GO_EMPTY_STONE, false, 0, "white");
}

void GoFightClass::resetEngineObjectData (void)
{
    this->theBaseObject->boardObject()->resetBoardObjectData();

    this->theGroupListArray[1] = new GoGroupListClass(this, 1, GO_BLACK_STONE, false, 0, 0);
    this->theGroupListArray[2] = new GoGroupListClass(this, 2, GO_WHITE_STONE, false, 0, 0);
    this->resetMarkedGroupLists();
    this->resetEmptyGroupLists();

    this->theCaptureCount = 0;
    this->theLastDeadStone = 0;
}

void GoFightClass::abendEngine (void)
{
}

void GoFightClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseLogit(s, str1_val);
}

void GoFightClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseAbend(s, str1_val);
}
