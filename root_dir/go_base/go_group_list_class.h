/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_GROUP_LST_CLASS_H__
#define __GO_GROUP_LST_CLASS_H__

#include "go_engine_class.h"

class GoGroupListClass {
  public:
    GoGroupListClass(GoEngineClass* engine_val,
                       int index_val,
                       int color_val,
                       int dead_val,
                       char const* big_stone_val,
                       char const* small_stone_val);
    ~GoGroupListClass();

    char const* objectName();
    GoEngineClass* engineObject();
    GoBaseClass* baseObject();

  private:
    GoEngineClass *theEngineObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
