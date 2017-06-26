/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_game_class.cpp
*/

#include <stdio.h>
#include "go_base_class.h"
#include "go_game_class.h"
//#include "go_move_class.h"

GoGameClass::GoGameClass (GoBaseClass* base_object_val):
        theBaseObject(base_object_val)
{
    this->resetGameObjectData();

    this->debug(true, "GoGameClass", "init");
}

GoFightClass* GoGameClass::fightObject (void)
{
    return this->baseObject()->fightObject();
}

GoMoveClass* GoGameClass::movesArray (int index_val)
{
    return this->theMovesArray[index_val];
}

void GoGameClass::setMovesArray (int index_val, GoMoveClass* val)
{
    this->theMovesArray[index_val] = val;
}

char GoGameClass::getOppositeColor (char color_val)
{
    switch (color_val) {
        case GO_BLACK_STONE:
            return GO_WHITE_STONE;

        case GO_WHITE_STONE:
            return GO_BLACK_STONE;

        default:
            this->abend("getOppositeColor", "color=" + color_val);
            return GO_EMPTY_STONE;
    }
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

    this->clearPassReceived();
    this->insertMoveToMoveList(move_val);
    this->fightObject()->enterWar(move_val);
    this->setNextColor(this->getOppositeColor(move_val->myColor()));
}

void GoGameClass::insertMoveToMoveList (GoMoveClass* move_val)
{
    this->setMovesArray(this->totalMoves(), move_val);
    this->incrementTotalMoves();
    this->setMaxMove(this->totalMoves());
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
    this->theNextColor = GO_BLACK_STONE;
    this->thePassReceived = false;
    this->theGameIsOver = false;
}

void GoGameClass::receiveSpecialMoveFromOpponent (char const *data_val)
{
    this->debug(true, "receiveSpecialMoveFromOpponent", data_val);

    if (!strcmp(data_val, "FORWARD")) {
        this->processForwardMove();
        this->theBaseObject->portObject()->transmitBoardData();
        return;
    }

    if (!strcmp(data_val, "DOUBLE_FORWARD")) {
        this->processDoubleForwardMove();
        this->theBaseObject->portObject()->transmitBoardData();
        return;
    }

    if (!strcmp(data_val, "BACKWARD")) {
        this->processBackwardMove();
        this->theBaseObject->portObject()->transmitBoardData();
        return;
    }

    if (!strcmp(data_val, "DOUBLE_BACKWARD")) {
        this->processDoubleBackwardMove();
        this->theBaseObject->portObject()->transmitBoardData();
        return;
    }

    if (!strcmp(data_val, "PASS")) {
        //this.processPassMove();
        //this.portObject().transmitBoardData();
        return;
    }

    if (!strcmp(data_val, "RESIGN")) {
        //this.processResignMove();
        return;
    }

    if (!strcmp(data_val, "BACK_TO_PLAY")) {
        //this.processBackToPlayMove();
        return;
    }

    if (!strcmp(data_val, "CONFIRM")) {
        //this.processConfirmMove();
        //this.portObject().transmitBoardData();
        return;
    }

    if (!strcmp(data_val, "PLAY_ANOTHER_GAME")) {
        //this.processPlayAnotherGameMove();
        return;
    }
}

void GoGameClass::processBackwardMove (void)
{
    this->debug(true, "processBackwardMove", "");
    this->thePassReceived = 0;
    if (this->theTotalMoves <= 0) {///this->theBaseObject->configObject()->handicapPoint()) {
        return;
    }
    this->theTotalMoves--;
    this->processTheWholeMoveList();
}

void GoGameClass::processDoubleBackwardMove (void)
{
    //this.debug(true, "goProcessBackwardMoveFromUi", "");
    this->thePassReceived = 0;
    if (this->theTotalMoves <= 0) {//this->theBaseObject->configObject()->handicapPoint()) {
        return;
    }
    this->theTotalMoves = 0;//(this->theBaseObject->configObject()->handicapPoint());
    this->processTheWholeMoveList();
}

void GoGameClass::processForwardMove (void)
{
    this->thePassReceived = 0;
    if (this->theTotalMoves > this->theMaxMove) {
        //this.abend("processForwardMove", "totalMoves=" + this.totalMoves_() + " maxMove=" + this.naxMove_());
        return;
    }
    if (this->theTotalMoves == this->theMaxMove) {
        return;
    }
    this->theTotalMoves++;
    this->processTheWholeMoveList();
}

void GoGameClass::processDoubleForwardMove (void)
{
    this->thePassReceived = 0;
    if (this->theTotalMoves > this->theMaxMove) {
        //this.abend("processDoubleForwardMove", "totalMoves=" + this.totalMoves() + " maxMove=" + this.maxMove_());
        return;
    }
    if (this->theTotalMoves == this->theMaxMove) {
        return;
    }
    this->setTotalMoves(this->theMaxMove);
    this->processTheWholeMoveList();
}

void GoGameClass::processTheWholeMoveList (void)
{
    this->theBaseObject->boardObject()->resetBoardObjectData();
    this->fightObject()->resetEngineObjectData();
    this->resetGameObjectPartialData();

    //this->debug(true, "processTheWholeMoveLst", "totalMoves=" + this.totalMoves());
    GoMoveClass *move;
    int i = 0;
    while (i < this->theTotalMoves) {
        move = this->theMovesArray[i];
        this->theBaseObject->fightObject()->enterWar(move);
        this->theNextColor = this->getOppositeColor(move->myColor());
        i += 1;
    }
}

void GoGameClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseLogit(s, str1_val);
}

void GoGameClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseAbend(s, str1_val);
}
