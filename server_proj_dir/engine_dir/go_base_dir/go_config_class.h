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

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    GoConfigClass(GoBaseClass* the_base_object);
    ~GoConfigClass(void) {}
    char const* objectName(void) {return "GoConfigClass";}

    int isValidCoordinates(int x_val, int y_val);
    int isValidCoordinate(int coordinate_val);

    int boardSize(void) {return theBoardSize;}
};
