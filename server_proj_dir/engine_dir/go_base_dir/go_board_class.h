/*
  Copyrights reserved
  Written by Paul Hwang
  File name:go_board_class.h
*/

#pragma once

class GoBaseClass;

class GoBoardClass {
    int debugOn_;
    GoBaseClass *theBaseObject;
    int theBoardArray[19][19];
    int theMarkedBoardArray[19][19];
    char theBoardOutputBuffer[1 + 3 + 1 + 19 * 19 + 3 * 2 + 2 * 2 + 32];
    int theBlackCapturedStones;
    int theWhiteCapturedStones;
    int theLastDeadX;
    int theLastDeadY;

    int isEmptySpace(int x_val, int y_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    GoBoardClass(int debug_on_val, GoBaseClass *the_base_object);
    ~GoBoardClass(void) {}
    char const *objectName(void) {return "GoBoardClass";}

    int boardArray(int x_val, int y_val) {return this->theBoardArray[x_val][y_val];}

    char *boardOutputBuffer() {return this->theBoardOutputBuffer;}
    void setBoardArray(int x_val, int y_val, int data_val) {this->theBoardArray[x_val][y_val] = data_val;}
    void addBlackCapturedStones(int val) {this->theBlackCapturedStones += val;}
    void addWhiteCapturedStones(int val) {this->theWhiteCapturedStones += val;}
    void setLastDeadStone(int x_val, int y_val) {this->theLastDeadX = x_val; theLastDeadY = y_val;}
    void clearLastDeadStone(void) {this->theLastDeadX = 19; theLastDeadY = 19;}
    void resetBoardObjectData(void);
    void resetMarkedBoardObjectData(void);
    void addStoneToBoard(int x_val, int y_val, int color_val);
    void encodeBoard(void);
    int stoneHasAir(int x_val, int y_val);
};
