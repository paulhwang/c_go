/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_config_class.h
*/

#pragma once

class GoBaseClass;

class GoConfigClass {
    GoBaseClass *theBaseObject;
    int theBoardSize;
    int theHandicapPoint;

    int isValidCoordinate(int coordinate_val) {return (0 <= coordinate_val) && (coordinate_val < this->theBoardSize);}

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

protected:
    friend class GoBoardClass;
    friend class GoGameClass;
    friend class GoFightClass;

    int boardSize(void) {return this->theBoardSize;}
    int handicapPoint(void) {return this->theHandicapPoint;}
    int isValidCoordinates(int x_val, int y_val) {return this->isValidCoordinate(x_val) && this->isValidCoordinate(y_val);}

public:
    GoConfigClass(GoBaseClass *the_base_object);
    ~GoConfigClass(void) {}
    char const *objectName(void) {return "GoConfigClass";}
};
