/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_game_class.cpp
*/

#include "../root_common.h"
#include "go_base_class.h"
#include "go_game_class.h"

GoGameClass::GoGameClass (GoBaseClass* base_object_val)
{
    this->theBaseObject = base_object_val;
    this->resetGameObjectData();

    if (1) {
        this->logit("GoGameClass", "init");
    }
}

GoGameClass::~GoGameClass (void)
{
}

char const* GoGameClass::objectName (void)
{
    return "GoGameClass";
}

GoBaseClass* GoGameClass::baseObject (void)
{
    return this->theBaseObject;
}

int GoGameClass::totalMoves (void)
{
    return this->theTotalMoves;
}

void GoGameClass::addNewMoveAndFight (GoMoveClass *move_val)
{
    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "move_val: (%i, %i, %i, %i)", move_val->xX(), move_val->yY(), move_val->myColor(), move_val->turnIndex());
        this->logit("addNewMoveAndFight", s);
    }

    if (this->gameIsOver()) {
        this->logit("addNewMoveAndFight", "two pass have entered");
        return;
    }

    //this->clearPassReceived();
    //this->insertMoveToMoveList(move_val);
    //this->engineObject().enterWar(move_val);
    //this->setNextColor(this.GO().getOppositeColor(move_val.myColor()));
}

int GoGameClass::gameIsOver (void)
{
    return 1;
}

void GoGameClass::resetGameObjectData (void)
{
    this->theMaxMove = 0;
    this->theTotalMoves = 0;
    //this.theMovesArray = [];
    this->resetGameObjectPartialData();
}

void GoGameClass::resetGameObjectPartialData (void)
{
    //this.theNextColor = this.GO().BLACK_STONE();
    //this.thePassReceived = false;
    //this.theGameIsOver = false;
}

void GoGameClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseObject()->goBaseLogit(s, str1_val);
}

void GoGameClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseObject()->goBaseAbend(s, str1_val);
}

