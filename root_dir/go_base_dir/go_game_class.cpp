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

int GoGameClass::maxMove (void)
{
    return this->theMaxMove;
}

void GoGameClass::setMaxMove (int max_move_val)
{
    this->theMaxMove = max_move_val;
}

int GoGameClass::totalMoves (void)
{
    return this->theTotalMoves;
}

void GoGameClass::setTotalMoves (int total_moves_val)
{
    this->theTotalMoves = total_moves_val;
}

void GoGameClass::incrementTotalMoves (void)
{
    this->theTotalMoves += 1;
}

void GoGameClass::decrementTotalMoves (void)
{
    this->theTotalMoves -= 1;
}

char GoGameClass::nextColor (void)
{
    return this->theNextColor;
}

void GoGameClass::setNextColor (char next_color_val)
{
    this->theNextColor = next_color_val;
}

int GoGameClass::passReceived (void) {
    return this->thePassReceived;
}

void GoGameClass::setPassReceived (void) {
    this->thePassReceived = true;
}

void GoGameClass::clearPassReceived (void) {
    this->thePassReceived = false;
}

int GoGameClass::gameIsOver (void)
{
    return this->theGameIsOver;
}

void GoGameClass::setGameIsOver (void) {
    this->theGameIsOver = true;
}

void GoGameClass::clearGameIsOver (void) {
    this->theGameIsOver = false;
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
    //this->engineObject().enterWar(move_val);
    this->setNextColor(this->getOppositeColor(move_val->myColor()));
}

void GoGameClass::insertMoveToMoveList (GoMoveClass* move_val)
{
    //this->setMovesArray(this->totalMoves(), move_val);
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

