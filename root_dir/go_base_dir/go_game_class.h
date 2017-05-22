/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_game_class.h
*/

#ifndef __GO_GAME_CLASS_H__
#define __GO_GAME_CLASS_H__

#include "go_base_class.h"

class GoGameClass
{
public:
    GoGameClass(GoBaseClass* the_base_object);
    ~GoGameClass(void);

    char const* objectName(void);
    GoBaseClass* baseObject(void);

    int totalMoves(void);

private:
    GoBaseClass *theBaseObject;
    int theTotalMoves;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
