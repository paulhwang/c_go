/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_figth_class.cpp
*/

#include <stdio.h>
#include "go_base_class.h"
#include "go_fight_class.h"

GoFightClass::GoFightClass (GoBaseClass* base_object_val):
    theBaseObject(base_object_val),
    theAbendEngineOn(0)
{
    this->resetEngineObjectData();
    this->debug(true, "GoFightClass", "init");
}

void GoFightClass::enterBattle (GoMoveClass* move_val)
{
    this->debug(true, "enterBattle", move_val->moveInfo());

    GoGroupClass *group = this->insertStoneToGroupList(move_val);
    if (!group) {
        return;
    }

    this->theBaseObject->boardObject()->addStoneToBoard(move_val->xX(), move_val->yY(), move_val->myColor());
    int dead_count = this->killOtherColorGroups(move_val, group);

    if (!group->groupHasAir()) {
        this->removeDeadGroup(group);
    }

    if (dead_count != 0) {
        if (move_val->myColor() == GO_BLACK_STONE) {
            this->theBaseObject->boardObject()->addBlackCapturedStones(dead_count);
        } else if (move_val->myColor() == GO_WHITE_STONE) {
            this->theBaseObject->boardObject()->addWhiteCapturedStones(dead_count);
        } else {
            this->abend("enterBattle", "bad color");
        }
    }
    this->abendEngine();
}

GoGroupClass* GoFightClass::insertStoneToGroupList (GoMoveClass* move_val)
{
    GoGroupListClass *g_list;

    if (move_val->myColor() == GO_BLACK_STONE) {
        g_list = this->blackGroupList();
    }
    else if (move_val->myColor() == GO_WHITE_STONE) {
        g_list = this->whiteGroupList();
    } else {
        this->abend("insertStoneToGroupList", move_val->moveInfo());
        return 0;
    }

    GoGroupClass *group = g_list->findCandidateGroup(move_val->xX(), move_val->yY());
    if (!group) {
        group = new GoGroupClass(g_list);
        group->insertStoneToGroup(move_val->xX(), move_val->yY(), false);
        g_list->insertGroupToGroupList(group);
        return group;
    }
}

int GoFightClass::killOtherColorGroups(GoMoveClass* move_val, GoGroupClass* group_val)
{
    this->theLastDeadStone = 0;

    int count;
    count =  this->killOtherColorGroup(group_val, move_val->xX() - 1, move_val->yY());
    count += this->killOtherColorGroup(group_val, move_val->xX() + 1, move_val->yY());
    count += this->killOtherColorGroup(group_val, move_val->xX(),     move_val->yY() - 1);
    count += this->killOtherColorGroup(group_val, move_val->xX(),     move_val->yY() + 1);
    return count;
}

int GoFightClass::killOtherColorGroup(GoGroupClass *group, int x_val, int y_val)
{
    GoGroupClass *his_group;

    if (!this->theBaseObject->configObject()->isValidCoordinates(x_val, y_val)) {
        return 0;
    }

    if (this->theBaseObject->boardObject()->theBoardArray[x_val][y_val] != group->hisColor()) {
        return 0;
    }

    his_group = this->getGroupByCoordinate(x_val, y_val, group->hisColor());
    if (!his_group) {
        this->abend("killOtherColorGroup", "null his_group");
        return 0;
    }

    if (his_group->groupHasAir()) {
        return 0;
    }

    int dead_count = his_group->stoneCount();
    if ((group->stoneCount() == 1) && (his_group->stoneCount() == 1)) {
        this->markLastDeadInfo(his_group);
    }

    this->removeDeadGroup(his_group);
    return dead_count;
}

GoGroupClass *GoFightClass::getGroupByCoordinate (int x_val, int y_val, int color_val)
{
    //goDebug("GoEngineObject.getGroupByCoordinate", color_val);
    GoGroupListClass *g_list;
    if ((color_val == GO_BLACK_STONE) || (color_val == GO_MARKED_DEAD_BLACK_STONE)) {
        g_list = this->blackGroupList();
    } else {
        g_list = this->whiteGroupList();
    }

    //goDebug("GoEngineObject.getGroupByCoordinate", "groupCount=" + g_list.groupCount());
    int i = 0;
    while (i < g_list->theGroupCount) {
        //goDebug("GoEngineObject.getGroupByCoordinate", "i=" + i);
        if (g_list->theGroupArray[i]->theExistMatrix[x_val][y_val]) {
            //goDebug("GoEngineObject.getGroupByCoordinate", "i=" + i);
            return g_list->theGroupArray[i];
        }
        i += 1;
    }
    return 0;
}

void GoFightClass::removeDeadGroup (GoGroupClass *group)
{
    group->removeDeadStoneFromBoard();
    if (group->myColor() == GO_BLACK_STONE) {
        this->blackGroupList()->removeGroupFromGroupList(group);
    } else {
        this->whiteGroupList()->removeGroupFromGroupList(group);
    }
}

void GoFightClass::markLastDeadInfo (GoGroupClass *group_val)
{
    /*
        this.setLastDeadStone(group_val.maxX(), group_val.maxY());

        if (group_val.maxX() !== group_val.minX()) {
            this.abend("markLastDeadInfo", "x: " + group_val.maxX() + "!=" + group_val.minX() + " count=" + group_val.stoneCount());
        }
        if (group_val.maxY() !== group_val.minY()) {
            this.abend("markLastDeadInfo", "y: " + group_val.maxY() + "!=" + group_val.minY() + " count=" + group_val.stoneCount());
        }
        if (!group_val.existMatrix(group_val.maxX(), group_val.maxY())) {
            this.abend("markLastDeadInfo", "exist_matrix");
        }
*/
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
    if (!this->theAbendEngineOn) {
        return;
    }
    this->debug(false, "abendEngine", "is ON ***");

    int stones_count = 0;
    int i = 0;
    while (i < GO_FIGHT_CLASS_GROUP_LIST_ARRAY_SIZE) {
        GoGroupListClass *group_list = this->theGroupListArray[i];
        //group_list->abendGroupList();
        //stones_count += group_list->totalStoneCount();
        i += 1;
    }

    /* check if a stone exist in both black and white group_lists */
    int black_stone_count = 0;
    int white_stone_count = 0;
    int board_size = this->theBaseObject->configObject()->boardSize();
    int x = 0;

    while (x < board_size) {
        int y = 0;
        while (y < board_size) {
/*
                if (this.blackGroupList().stoneExistWithinMe(x, y)) {
                    if (this.whiteGroupList().stoneExistWithinMe(x, y)) {
                        this.abend("abendEngine", "(" + x + "," + y + ")");
                    }
                    black_stone_count += 1;
                }
                if (this.whiteGroupList().stoneExistWithinMe(x, y)) {
                   white_stone_count += 1;
                }
                y += 1;
*/
        }
        x += 1;
    }

    if (this->blackGroupList()->totalStoneCount() != black_stone_count) {
        this->abend("abendEngine", "black_stone count does not match");
    }
    if (this->whiteGroupList()->totalStoneCount() != white_stone_count) {
        this->abend("abendEngine", "black_stone count does not match");
    }
/*

        //this.goLog("abendEngine", this.gameObject().gameIsOver());
        if (this.gameObject().gameIsOver()) {
            if (this.boardSize() * this.boardSize() !== stones_count) {
                this.abend("abendEngine", "stones_count=" + stones_count);
            }
        }
*/
    this->emptyGroupList()->abendGroupList();
    this->blackGroupList()->abendGroupList();
    this->whiteGroupList()->abendGroupList();
    this->blackDeadGroupList()->abendGroupList();
    this->whiteDeadGroupList()->abendGroupList();
    this->blackEmptyGroupList()->abendGroupList();
    this->whiteEmptyGroupList()->abendGroupList();
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
