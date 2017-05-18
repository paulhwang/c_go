/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "./go_base_common.h"

class go_move_class {
  public:
    go_move_class();
    ~go_move_class();

  private:
    void debug(int debug_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
