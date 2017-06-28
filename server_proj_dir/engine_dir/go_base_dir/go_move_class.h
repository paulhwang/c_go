/*
  Copyrights reserved
  Written by Paul Hwang
  File name" go_move_class.h
*/

#pragma once

class GoBaseClass;

class GoMoveClass {
    GoBaseClass *theBaseObject;
    int theX;
    int theY;
    int theMyColor;
    int theTurnIndex;
    char theMoveInfo[32];

    void moveObjectDecode(char const *str_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

protected:
    friend class GoGameClass;
    friend class GoFightClass;
    friend class GoPortClass;

    int xX(void) {return this->theX;}
    int yY(void) {return this->theY;}
    int myColor(void) {return this->theMyColor;}
    int turnIndex(void) {return this->theTurnIndex;}
    char *moveInfo(void) {return this->theMoveInfo;}

public:
    GoMoveClass(GoBaseClass *base_object_val, char const *encoded_move_val);
    ~GoMoveClass(void) {}
    char const* objectName(void) {return "GoMoveClass";}
};
