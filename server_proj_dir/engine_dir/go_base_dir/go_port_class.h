/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_port_class.h
*/

#pragma once

class GoBaseClass;

class GoPortClass {
    GoBaseClass *theBaseObject;

    void parseGameData(char const *str_val);
    void transmitOutputData(char const *data_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    GoPortClass(GoBaseClass *base_object_val);
    ~GoPortClass(void) {}
    char const *objectName(void) {return "GoPortClass";}

    void receiveInputData(char const *str_val);
    void transmitBoardData (void);
};
