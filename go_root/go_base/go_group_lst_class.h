/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_GROUP_LST_CLASS_H__
#define __GO_GROUP_LST_CLASS_H__

class GoEngineClass;

class GoGroupListClass {
  public:
    GoGroupListClass(GoEngineClass* engine_val,
                       int index_val,
                       int color_val,
                       int dead_val,
                       char* big_stone_val,
                       char* small_stone_val);
    ~GoGroupListClass();

  private:
    GoEngineClass *theEngineObject;
    char const* objectName();
    GoEngineClass* engineObject();
    GoBaseClass* baseObject();
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
