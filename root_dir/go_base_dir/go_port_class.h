/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_PORT_CLASS_H__
#define __GO_PORT_CLASS_H__

#include "go_base_class.h"

class GoPortClass {
  public:
    GoPortClass(GoBaseClass* base_object_val);
    ~GoPortClass(void);

    char const* objectName(void);
    GoBaseClass* baseObject(void);
    GoBoardClass* boardObject(void);

    void receiveStringData (char const* str_val);

  private:
    GoBaseClass *theBaseObject;

    void transmitBoardData (void);
    void aMoveIsPlayed(char const* str_val);
    void aSpecialMoveIsPlayed(char const* str_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
