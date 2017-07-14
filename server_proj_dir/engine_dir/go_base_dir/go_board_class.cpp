/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_board_class.cpp
*/

#include <stdio.h>
#include "go_base_class.h"
#include "go_board_class.h"

GoBoardClass::GoBoardClass (GoBaseClass *base_object_val):
    theBaseObject(base_object_val)
{
    this->resetBoardObjectData();
    this->debug(false, "GoBoardClass", "init");
}

void GoBoardClass::addStoneToBoard (int x_val, int y_val, int color_val)
{
    if (!this->theBaseObject->configObject()->isValidCoordinates(x_val, y_val)) {
        this->abend("addStoneToBoard", "bad coordinate");
        return;
    }

    this->theBoardArray[x_val][y_val] = color_val;
}

void GoBoardClass::encodeBoard (void) {
    char *buf_ptr = this->theBoardOutputBuffer;

    phwangEncodeNumber(buf_ptr, this->theBaseObject->gameObject()->totalMoves(), 3);
    buf_ptr += 3;
    phwangEncodeNumber(buf_ptr, this->theBaseObject->gameObject()->nextColor(), 1);
    buf_ptr++;

    int board_size = this->theBaseObject->configObject()->boardSize();
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            *buf_ptr++ = this->theBoardArray[i][j] + '0';
        }
    }

    phwangEncodeNumber(buf_ptr, this->theBlackCapturedStones, 3);
    buf_ptr += 3;
    phwangEncodeNumber(buf_ptr, this->theWhiteCapturedStones, 3);
    buf_ptr += 3;

    phwangEncodeNumber(buf_ptr, this->theLastDeadX, 2);
    buf_ptr += 2;
    phwangEncodeNumber(buf_ptr, this->theLastDeadY, 2);
    buf_ptr += 2;

    *buf_ptr = 0;

    this->debug(false, "encodeBoard", this->theBoardOutputBuffer);
}

void GoBoardClass::resetBoardObjectData (void) {
    int board_size = this->theBaseObject->configObject()->boardSize();
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            this->theBoardArray[i][j] = GO_EMPTY_STONE;
            this->theMarkedBoardArray[i][j] = GO_EMPTY_STONE;
        }
    }
    this->theBlackCapturedStones = 0;
    this->theWhiteCapturedStones = 0;
    this->theLastDeadX = 19;
    this->theLastDeadY = 19;
}

void GoBoardClass::resetMarkedBoardObjectData (void)
{

}

int GoBoardClass::stoneHasAir (int x_val, int y_val)
{
    if (this->isEmptySpace(x_val, y_val - 1)) {
        return true;
    }
    if (this->isEmptySpace(x_val, y_val + 1)) {
        return true;
    }
    if (this->isEmptySpace(x_val - 1, y_val)) {
        return true;
    }
    if (this->isEmptySpace(x_val + 1, y_val)) {
        return true;
    }
    return false;
}

int GoBoardClass::isEmptySpace (int x_val, int y_val)
{
    if (!this->theBaseObject->configObject()->isValidCoordinates(x_val, y_val)) {
        return false;
    }
    if (this->theBoardArray[x_val][y_val] != GO_EMPTY_STONE) {
        return false;
    }
    return true;
}

void GoBoardClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseLogit(s, str1_val);
}

void GoBoardClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theBaseObject->goBaseAbend(s, str1_val);
}
