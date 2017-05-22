/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_board_class.cpp
*/

#include "../root_common.h"
#include "go_base_class.h"
#include "go_board_class.h"

GoBoardClass::GoBoardClass (GoBaseClass* base_object_val) {
    this->theBaseObject = base_object_val;
    this->resetBoardObjectData();

    if (1) {
        this->logit("init", "");
    }
}

GoBoardClass::~GoBoardClass (void) {
}

char const* GoBoardClass::objectName (void) {
    return "GoBoardClass";
}

GoBaseClass* GoBoardClass::baseObject (void) {
    return this->theBaseObject;
}

GoConfigClass* GoBoardClass::configObject (void) {
    return this->baseObject()->configObject();
}

int GoBoardClass::boardSize (void)
{
    return this->configObject()->boardSize();
}

char GoBoardClass::boardArray (int x_val, int y_val)
{
    return this->theBoardArray[x_val][y_val];
}

char GoBoardClass::markedBoardArray (int x_val, int y_val)
{
    return this->theMarkedBoardArray[x_val][y_val];
}

void GoBoardClass::setBoardArray (int x_val, int y_val, char data_val)
{
    this->theBoardArray[x_val][y_val] = data_val;
}

void GoBoardClass::setMarkedBoardArray (int x_val, int y_val, char data_val)
{
    this->theMarkedBoardArray[x_val][y_val] = data_val;
}

void GoBoardClass::resetMarkedBoardObjectData (void) {

}

void GoBoardClass::addStoneToBoard (int x_val, int y_val, char color_val)
{
//    if (!this.GO().isValidCoordinates(x_val, y_val, this.configObject().boardSize())) {
//        this.goAbend("addStoneToBoard", "x=" + x_val + " y=" + y_val);
//        return;
//    }

    this->setBoardArray(x_val, y_val, color_val);
}

void GoBoardClass::encodeBoard (char* buf_ptr) {
    char *buf_ptr0 = buf_ptr;
    int i = 0;
    while (i < this->boardSize()) {
        int j = 0;
        while (j < this->boardSize()) {
            *buf_ptr0++ = this->theBoardArray[i][j];
            j += 1;
        }
        i += 1;
    }
    *buf_ptr0 = 0;

    if (0) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "data=%s", buf_ptr);
        this->logit("encodeBoard", s);
    }
}

void GoBoardClass::resetBoardObjectData (void) {
    int i = 0;
    while (i < this->boardSize()) {
        int j = 0;
        while (j < this->boardSize()) {
            this->theBoardArray[i][j] = GO_EMPTY_STONE;
            this->theMarkedBoardArray[i][j] = GO_EMPTY_STONE;
            j += 1;
        }
        i += 1;
    }
}

void GoBoardClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseObject()->goBaseLogit(s, str1_val);
}

void GoBoardClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->baseObject()->goBaseAbend(s, str1_val);
}

