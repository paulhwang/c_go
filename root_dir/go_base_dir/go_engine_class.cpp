/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_engine_class.cpp
*/

#include "../root_common.h"
#include "../../includes/types.h"
#include "go_base_class.h"
#include "go_engine_class.h"

GoEngineClass::GoEngineClass (GoBaseClass* base_object_val) {
  this->theBaseObject = base_object_val;
  this->resetEngineObjectData();

  if (1) {
    this->logit("GoEngineClass", "init");
  }
}

GoEngineClass::~GoEngineClass (void)
{
}

char const* GoEngineClass::objectName (void)
{
  return "GoEngineClass";
}

GoBaseClass* GoEngineClass::baseObject (void)
{
  return this->theBaseObject;
}

GoBoardClass* GoEngineClass::boardObject (void)
{
  return this->baseObject()->boardObject();
}

void GoEngineClass::clearLastDeadStone (void)
{
    this->theLastDeadStone = 0;
}

void GoEngineClass::enterWar (GoMoveClass* move_val)
{
    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "move_val: (%i, %i, %i, %i)", move_val->xX(), move_val->yY(), move_val->myColor(), move_val->turnIndex());
        this->logit("enterWar", s);
    }

    GoGroupClass* group = this->insertStoneToGroupList(move_val);
    //this->boardObject()->addStoneToBoard(move_val->xX(), move_val->yY(), move_val->myColor());
    int dead_count = this->killOtherColorGroups(move_val, group);

     this->abendEngine();
}

GoGroupClass* GoEngineClass::insertStoneToGroupList (GoMoveClass* move_val)
{
}

int GoEngineClass::killOtherColorGroups(GoMoveClass* move_val, GoGroupClass* group_val)
{
    int count;
    this->clearLastDeadStone();
    count = this->killOtherColorGroup(group_val, move_val->xX() - 1, move_val->yY());
    count += this->killOtherColorGroup(group_val, move_val->xX() + 1, move_val->yY());
    count += this->killOtherColorGroup(group_val, move_val->xX(), move_val->yY() - 1);
    count += this->killOtherColorGroup(group_val, move_val->xX(), move_val->yY() + 1);
    return count;
}

int GoEngineClass::killOtherColorGroup(GoGroupClass* group, int x_val, int y_val)
{
    return 0;
}

void GoEngineClass::resetMarkedGroupLists (void)
{
    this->theGroupListArray[3] = new GoGroupListClass(this, 3, GO_BLACK_STONE, true, "black", "gray");
    this->theGroupListArray[4] = new GoGroupListClass(this, 4, GO_WHITE_STONE, true, "white", "gray");
    this->boardObject()->resetMarkedBoardObjectData();
}

void GoEngineClass::resetEmptyGroupLists (void)
{
    this->theGroupListArray[0] = new GoGroupListClass(this, 0, GO_EMPTY_STONE, false, null, null);
    this->theGroupListArray[5] = new GoGroupListClass(this, 5, GO_EMPTY_STONE, false, null, "black");
    this->theGroupListArray[6] = new GoGroupListClass(this, 6, GO_EMPTY_STONE, false, null, "white");
}

void GoEngineClass::resetEngineObjectData (void)
{
    this->theGroupListCount = GO_GROUP_LIST_ARRAY_SIZE;
    //this.theGroupListArray = [this.groupListCount()];
    this->theGroupListArray[1] = new GoGroupListClass(this, 1, GO_BLACK_STONE, false, null, null);
    this->theGroupListArray[2] = new GoGroupListClass(this, 2, GO_WHITE_STONE, false, null, null);
    this->resetMarkedGroupLists();
    this->resetEmptyGroupLists();

    this->theCaptureCount = null;
    this->theLastDeadStone = null;

    this->theBlackCaptureStones = 0;
    this->theWhiteCaptureStones = 0;
}

void GoEngineClass::abendEngine (void)
{
}

void GoEngineClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseObject()->goBaseLogit(s, str1_val);
}

void GoEngineClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseObject()->goBaseAbend(s, str1_val);
}

