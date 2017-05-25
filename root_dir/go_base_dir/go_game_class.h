/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_game_class.h
*/

#pragma once

class GoMoveClass;

#define GO_MAX_MOVES_ARRAY_SIZE 1024
#include "go_base_class.h"

class GoGameClass
{
    GoBaseClass *theBaseObject;
    int theTotalMoves;
    int theMaxMove;
    GoMoveClass* theMovesArray[GO_MAX_MOVES_ARRAY_SIZE];
    char theNextColor;
    int thePassReceived;
    int theGameIsOver;

    GoEngineClass* engineObject(void);
    char getOppositeColor(char color_val);
    void insertMoveToMoveList(GoMoveClass* move_val);
    void resetGameObjectData(void);
    void resetGameObjectPartialData(void);

    GoMoveClass* movesArray(int index_val);
    void setMovesArray(int index_val, GoMoveClass* val);

    int maxMove (void) {return theMaxMove;}
    void setMaxMove(int max_move_val) {theMaxMove = max_move_val;}
    void setTotalMoves(int total_moves_val) {theTotalMoves = total_moves_val;}
    void incrementTotalMoves(void) {theTotalMoves++;}
    void decrementTotalMoves(void) {theTotalMoves--;}
    char nextColor(void) {return theNextColor;}
    void setNextColor(char next_color_val) {theNextColor = next_color_val;}
    int passReceived(void) {return thePassReceived;}
    void setPassReceived(void) {thePassReceived = true;}
    void clearPassReceived(void) {thePassReceived = false;}
    int gameIsOver(void) {return theGameIsOver;}
    void setGameIsOver(void) {theGameIsOver = true;}
    void clearGameIsOver(void) {theGameIsOver = false;}

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GoGameClass(GoBaseClass* the_base_object);
    ~GoGameClass(void);

    void addNewMoveAndFight(GoMoveClass *move_val);

    int totalMoves(void) {return theTotalMoves;}

    GoBaseClass* baseObject(void) {return theBaseObject;}
    char const* objectName(void) {return "GoGameClass";}
};
