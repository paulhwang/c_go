/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_CONFIG_CLASS_H__
#define __GO_CONFIG_CLASS_H__

#include "go_base_class.h"

class GoConfigClass {
  public:
    GoConfigClass(GoBaseClass* the_base_object);
    ~GoConfigClass(void);

    char const* objectName(void);
    GoBaseClass* baseObject();
    int boardSize(void);
    int isValidCoordinates(int x_val, int y_val);
    int isValidCoordinate(int coordinate_val);

  private:
    GoBaseClass *theBaseObject;
    int theBoardSize;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
