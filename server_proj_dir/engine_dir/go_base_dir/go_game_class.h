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
    int debugOn_;
    GoBaseClass *theBaseObject;
    GoMoveClass *theMovesArray[GO_GAME_CLASS_MAX_MOVES_ARRAY_SIZE];
    int theTotalMoves;
    int theMaxMove;
    int theNextColor;
    int thePassReceived;
    int theGameIsOver;

    void insertMoveToMoveList(GoMoveClass* move_val);
    void resetGameObjectData(void);
    void resetGameObjectPartialData(void);

    void processTheWholeMoveList(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    GoGameClass(int debug_on_val, GoBaseClass *the_base_object);
    ~GoGameClass(void);
    char const *objectName(void) {return "GoGameClass";}

    int totalMoves(void) {return this->theTotalMoves;}
    int nextColor(void) {return this->theNextColor;}

    void addNewMoveAndFight(GoMoveClass *move_val);
    void receiveSpecialMoveFromOpponent(char const *data_val);
    void processBackwardMove(void);
    void processDoubleBackwardMove(void);
    void processForwardMove(void);
    void processDoubleForwardMove(void);
};
