/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_BOARD_CLASS_H__
#define __GO_BOARD_CLASS_H__

class GoBaseClass;

class GoBoardClass {
  public:
    GoBoardClass(GoBaseClass* the_base_object);
    ~GoBoardClass();

    void resetMarkedBoardObjectData();

  private:
    GoBaseClass *the_base_object;
    char const* object_name();
    GoBaseClass* base_object();
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
