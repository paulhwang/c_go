/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_config_class.h
*/

#pragma once

#include "go_base_class.h"

class GoConfigClass {
    GoBaseClass *theBaseObject;
    int theBoardSize;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GoConfigClass(GoBaseClass* the_base_object);
    ~GoConfigClass(void);

    int isValidCoordinates(int x_val, int y_val);
    int isValidCoordinate(int coordinate_val);

    int boardSize(void) {return theBoardSize;}
    GoBaseClass* baseObject(void) {return theBaseObject;}
    char const* objectName(void) {return "GoConfigClass";}
};
