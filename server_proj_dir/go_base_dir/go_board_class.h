/*
  Copyrights reserved
  Written by Paul Hwang
  File name:go_board_class.h
*/

#pragma once

class GoBaseClass;
class GoConfigClass;
#include "go_base_class.h"

class GoBoardClass {
    GoBaseClass *theBaseObject;
    GoConfigClass* configObject(void);

    char theBoardArray[19][19];
    char theMarkedBoardArray[19][19];

    int boardSize (void);
    char boardArray(int x_val, int y_val);
    char markedBoardArray(int x_val, int y_val);
    void setBoardArray(int x_val, int y_val, char data_val);
    void setMarkedBoardArray(int x_val, int y_val, char data_val);

    void resetBoardObjectData (void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GoBoardClass(GoBaseClass* the_base_object);
    ~GoBoardClass(void);

    void resetMarkedBoardObjectData(void);
    void addStoneToBoard(int x_val, int y_val, char color_val);
    void encodeBoard(char* buf_ptr);

    GoBaseClass* baseObject(void) {return theBaseObject;}
    char const* objectName(void) {return "GoBoardClass";}
};