/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_BOARD_CLASS_H__
#define __GO_BOARD_CLASS_H__

class GoBaseClass;

class go_board_class {
  public:
    go_board_class(GoBaseClass* the_base_object);
    ~go_board_class();

    void resetMarkedBoardObjectData();

  private:
    GoBaseClass *the_base_object;
    char const* object_name();
    GoBaseClass* base_object();
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
