/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_game_class.h
*/

#ifndef __GO_GAME_CLASS_H__
#define __GO_GAME_CLASS_H__

class GoMoveClass;

#define GO_MAX_MOVES_ARRAY_SIZE 1024
#include "go_base_class.h"

class GoGameClass
{
public:
    GoGameClass(GoBaseClass* the_base_object);
    ~GoGameClass(void);

    char const* objectName(void);
    GoBaseClass* baseObject(void);

    int totalMoves(void);
    void addNewMoveAndFight(GoMoveClass *move_val);

private:
    GoBaseClass *theBaseObject;
    int theTotalMoves;
    int theMaxMove;
    GoMoveClass* theMovesArray[GO_MAX_MOVES_ARRAY_SIZE];
    char theNextColor;
    int thePassReceived;
    int theGameIsOver;

    GoEngineClass* engineObject(void);

    GoMoveClass* movesArray(int index_val);
    void setMovesArray(int index_val, GoMoveClass* val);
    int maxMove (void);
    void setMaxMove(int max_move_val);
    void setTotalMoves(int total_moves_val);
    void incrementTotalMoves(void);
    void decrementTotalMoves(void);
    char nextColor(void);
    void setNextColor(char next_color_val);
    char getOppositeColor(char color_val);
    int passReceived(void);
    void setPassReceived(void);
    void clearPassReceived(void);
    int gameIsOver(void);
    void setGameIsOver(void);
    void clearGameIsOver(void);

    void insertMoveToMoveList(GoMoveClass* move_val);
    void resetGameObjectData(void);
    void resetGameObjectPartialData(void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
