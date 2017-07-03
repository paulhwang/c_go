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
    theAbendEngineOn(1)
{
    this->resetEngineObjectData();
    this->debug(true, "GoFightClass", "init");
}

GoFightClass::~GoFightClass(void)
{
    for (int i = 0; i < GO_FIGHT_CLASS_GROUP_LIST_ARRAY_SIZE; i++) {
        if (this->theGroupListArray[i]) {
            this->theGroupListArray[i]->~GoGroupListClass();
            this->theGroupListArray[i] = 0;
        }
    }
}

void GoFightClass::enterBattle (GoMoveClass* move_val)
{
    this->debug(true, "enterBattle", move_val->moveInfo());

    this->theBaseObject->boardObject()->addStoneToBoard(move_val->xX(), move_val->yY(), move_val->myColor());
    GoGroupClass *my_group = this->insertStoneToGroupList(move_val);
    if (!my_group) {
        this->abend("enterBattle", "fail in insertStoneToGroupList");
        return;
    }

    int dead_count = this->killOtherColorGroups(move_val, my_group);

    if (!my_group->groupHasAir()) {
        this->removeDeadGroup(my_group);
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

    group->insertStoneToGroup(move_val->xX(), move_val->yY(), false);

    int dummy_count = 0;
    GoGroupClass *group2;
    while (1) {
        group2 = g_list->findOtherCandidateGroup(group, move_val->xX(), move_val->yY());
        if (!group2) {
            break;
        }
        dummy_count += 1;
        group->mergeWithOtherGroup(group2);
        g_list->removeGroupFromGroupList(group2);
    }
    if (dummy_count > 3) {
        this->abend("insertStoneToGroupList", "dummy_count");
    }
    return group;
}

int GoFightClass::killOtherColorGroups(GoMoveClass* move_val, GoGroupClass* my_group_val)
{
    int count;
    count =  this->killOtherColorGroup(my_group_val, move_val->xX() - 1, move_val->yY());
    count += this->killOtherColorGroup(my_group_val, move_val->xX() + 1, move_val->yY());
    count += this->killOtherColorGroup(my_group_val, move_val->xX(),     move_val->yY() - 1);
    count += this->killOtherColorGroup(my_group_val, move_val->xX(),     move_val->yY() + 1);
    return count;
}

int GoFightClass::killOtherColorGroup(GoGroupClass *my_group_val, int x_val, int y_val)
{
    GoGroupClass *his_group;

    if (!this->theBaseObject->configObject()->isValidCoordinates(x_val, y_val)) {
        return 0;
    }

    if (this->theBaseObject->boardObject()->boardArray(x_val, y_val) != my_group_val->hisColor()) {
        return 0;
    }

    his_group = this->getGroupByCoordinate(x_val, y_val, my_group_val->hisColor());
    if (!his_group) {
        this->abend("killOtherColorGroup", "null his_group");
        return 0;
    }

    if (his_group->groupHasAir()) {
        return 0;
    }

    int dead_count = his_group->stoneCount();
    if ((my_group_val->stoneCount() == 1) && (his_group->stoneCount() == 1)) {
        this->markLastDeadInfo(his_group);
    }

    this->removeDeadGroup(his_group);
    return dead_count;
}

GoGroupClass *GoFightClass::getGroupByCoordinate (int x_val, int y_val, int color_val)
{
    GoGroupListClass *g_list;
    if ((color_val == GO_BLACK_STONE) || (color_val == GO_MARKED_DEAD_BLACK_STONE)) {
        g_list = this->blackGroupList();
    } else {
        g_list = this->whiteGroupList();
    }

    for (int i = 0; i < g_list->groupCount(); i++) {
        if (g_list->groupArray(i)->theExistMatrix[x_val][y_val]) {
            return g_list->groupArray(i);
        }
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
    this->theBaseObject->boardObject()->setLastDeadStone(group_val->theMaxX, group_val->theMaxY);

    if (group_val->theMaxX != group_val->theMinX) {
        this->abend("markLastDeadInfo", "bad x");
    }
    if (group_val->theMaxY != group_val->theMinY) {
         this->abend("markLastDeadInfo", "bad y");
    }
    if (!group_val->theExistMatrix[group_val->theMaxX][group_val->theMaxY]) {
        this->abend("markLastDeadInfo", "exist_matrix");
    }
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

    /*
    int stones_count = 0;
    int i = 0;
    while (i < GO_FIGHT_CLASS_GROUP_LIST_ARRAY_SIZE) {
        GoGroupListClass *group_list = this->theGroupListArray[i];
        stones_count += group_list->theTotalStoneCount;
        i += 1;
    }
    */

    /* check if a stone exist in both black and white group_lists */
    int black_stone_count = 0;
    int white_stone_count = 0;
    int board_size = this->theBaseObject->configObject()->boardSize();

    for (int x = 0; x < board_size; x++) {
        for (int y = 0; y < board_size; y++) {
            if (this->theBaseObject->boardObject()->boardArray(x, y) == GO_BLACK_STONE) {
                black_stone_count++;
                if (!this->blackGroupList()->stoneExistWithinMe(x, y)) {
                    this->abend("abendEngine", "black stone does not exist in blackGroupList");
                }
            }
            else if (this->theBaseObject->boardObject()->boardArray(x, y) == GO_WHITE_STONE) {
                white_stone_count++;
                if (!this->whiteGroupList()->stoneExistWithinMe(x, y)) {
                    this->abend("abendEngine", "white stone does not exist in whiteGroupList");
                }
            }
            else if (this->theBaseObject->boardObject()->boardArray(x, y) == GO_EMPTY_STONE) {
            }
            else {
                this->abend("abendEngine", "bad color in theBoardArray");
            }
        }
    }

    int black_stone_count1 = 0;
    int white_stone_count1 = 0;
    for (int x = 0; x < board_size; x++) {
        for (int y = 0; y < board_size; y++) {
            if (this->blackGroupList()->stoneExistWithinMe(x, y)) {
                black_stone_count1++;

                if (this->theBaseObject->boardObject()->boardArray(x, y) != GO_BLACK_STONE) {
                    this->abend("abendEngine", "black stone does not exist in theBoardArray");
                }

                if (this->whiteGroupList()->stoneExistWithinMe(x, y)) {
                    this->abend("abendEngine", "balck exist in wrong group list");
                }
            }
            if (this->whiteGroupList()->stoneExistWithinMe(x, y)) {
                white_stone_count1++;

                if (this->theBaseObject->boardObject()->boardArray(x, y) != GO_WHITE_STONE) {
                    this->abend("abendEngine", "black stone does not exist in theBoardArray");
                }
            }
        }
    }

    if (black_stone_count != black_stone_count1) {
        this->abend("abendEngine", "black_stone_count does not match");
    }
    if (white_stone_count != white_stone_count1) {
        this->abend("abendEngine", "white_stone_count does not match");
    }

    if (this->blackGroupList()->totalStoneCount() != black_stone_count) {
        printf("abendEngine   %d\n", this->blackGroupList()->totalStoneCount());
        printf("abendEngine   %d\n", black_stone_count);
        this->abend("abendEngine", "black_stone count does not match");
    }
    if (this->whiteGroupList()->totalStoneCount() != white_stone_count) {
        printf("abendEngine   %d\n", this->whiteGroupList()->totalStoneCount());
        printf("abendEngine   %d\n", white_stone_count);
        this->abend("abendEngine", "white count does not match");
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
