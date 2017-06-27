/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_game_class.h
*/

#pragma once

class GoMoveClass;
class GoBaseClass;

class GoGameClass
{
#define GO_GAME_CLASS_MAX_MOVES_ARRAY_SIZE 1024
    GoBaseClass *theBaseObject;
    GoMoveClass *theMovesArray[GO_GAME_CLASS_MAX_MOVES_ARRAY_SIZE];
    int theTotalMoves;
    int theMaxMove;
    char theNextColor;
    int thePassReceived;
    int theGameIsOver;

    char getOppositeColor(char color_val);
    void insertMoveToMoveList(GoMoveClass* move_val);
    void resetGameObjectData(void);
    void resetGameObjectPartialData(void);

    void processBackwardMove(void);
    void processDoubleBackwardMove(void);
    void processForwardMove(void);
    void processDoubleForwardMove(void);
    void processTheWholeMoveList(void);
    void addNewMoveAndFight(GoMoveClass *move_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

protected:
    friend class GoPortClass;

    void receiveSpecialMoveFromOpponent(char const *data_val);

public:
    GoGameClass(GoBaseClass *the_base_object);
    ~GoGameClass(void) {}
    char const *objectName(void) {return "GoGameClass";}
};
