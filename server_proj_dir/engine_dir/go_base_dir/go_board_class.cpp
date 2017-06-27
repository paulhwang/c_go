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

void GoBoardClass::addStoneToBoard (int x_val, int y_val, char color_val)
{
    if (!this->theBaseObject->configObject()->isValidCoordinates(x_val, y_val)) {
        this->abend("addStoneToBoard", "bad coordinate");
        return;
    }

    this->theBoardArray[x_val][y_val] = color_val;
}

char *GoBoardClass::encodeBoard (void) {
    char *buf_ptr = this->theBoardOutputBuffer;
    int board_size = this->theBaseObject->configObject()->boardSize();
    int i = 0;
    while (i < board_size) {
        int j = 0;
        while (j < board_size) {
            *buf_ptr++ = this->theBoardArray[i][j];
            j += 1;
        }
        i += 1;
    }

    phwangEncodeNumber(buf_ptr, this->theBlackCapturedStones, 3);
    buf_ptr += 3;
    phwangEncodeNumber(buf_ptr, this->theWhiteCapturedStones, 3);
    buf_ptr += 3;

    *buf_ptr = 0;

    this->debug(true, "encodeBoard", this->theBoardOutputBuffer);
    return this->theBoardOutputBuffer;
}

void GoBoardClass::resetBoardObjectData (void) {
    int board_size = this->theBaseObject->configObject()->boardSize();
    int i = 0;
    while (i < board_size) {
        int j = 0;
        while (j < board_size) {
            this->theBoardArray[i][j] = GO_EMPTY_STONE;
            this->theMarkedBoardArray[i][j] = GO_EMPTY_STONE;
            j += 1;
        }
        i += 1;
    }
    this->theBlackCapturedStones = 0;
    this->theWhiteCapturedStones = 0;
}

void GoBoardClass::resetMarkedBoardObjectData (void) {

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
