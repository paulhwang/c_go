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

    char theBoardArray[19][19];
    char theMarkedBoardArray[19][19];

    char boardArray(int x_val, int y_val);
    char markedBoardArray(int x_val, int y_val);
    void setBoardArray(int x_val, int y_val, char data_val);
    void setMarkedBoardArray(int x_val, int y_val, char data_val);

    void resetBoardObjectData (void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    GoBoardClass(GoBaseClass* the_base_object);
    ~GoBoardClass(void) {}
    char const* objectName(void) {return "GoBoardClass";}

    void resetMarkedBoardObjectData(void);
    void addStoneToBoard(int x_val, int y_val, char color_val);
    void encodeBoard(char* buf_ptr);
};
