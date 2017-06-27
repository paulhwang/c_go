/*
  Copyrights reserved
  Written by Paul Hwang
  File name:go_board_class.h
*/

#pragma once

class GoBaseClass;

class GoBoardClass {
    GoBaseClass *theBaseObject;
    char theBoardArray[19][19];
    char theMarkedBoardArray[19][19];
    char theBoardOutputBuffer[19 * 19 + 3 * 2 + 16];
    int theBlackCapturedStones;
    int theWhiteCapturedStones;

    int isEmptySpace(int x_val, int y_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

protected:
    friend class GoGameClass;
    friend class GoFightClass;
    friend class GoPortClass;
    friend class GoGroupClass;

    void addBlackCapturedStones(int val) {this->theBlackCapturedStones += val;}
    void addWhiteCapturedStones(int val) {this->theWhiteCapturedStones += val;}
    void resetBoardObjectData (void);
    void resetMarkedBoardObjectData(void);
    void addStoneToBoard(int x_val, int y_val, char color_val);
    char *encodeBoard(void);
    int stoneHasAir(int x_val, int y_val);

public:
    GoBoardClass(GoBaseClass *the_base_object);
    ~GoBoardClass(void) {}
    char const *objectName(void) {return "GoBoardClass";}
};
