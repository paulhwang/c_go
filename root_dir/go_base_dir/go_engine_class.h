/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_ENGINE_CLASS_H__
#define __GO_ENGINE_CLASS_H__

class GoGroupListClass;
#include "go_base_class.h"

#define GO_GROUP_LIST_ARRAY_SIZE 7

class GoEngineClass {
  public:
    GoEngineClass(GoBaseClass* base_object_val);
    ~GoEngineClass();

    char const* objectName();
    void resetEngineObjectData();
    GoBaseClass* baseObject();
    GoBoardClass* boardObject();

  private:
    GoBaseClass *theBaseObject;
    int theGroupListCount;
    GoGroupListClass* theGroupListArray[GO_GROUP_LIST_ARRAY_SIZE];
    int theBlackCaptureStones;
    int theWhiteCaptureStones;
    char* theCaptureCount;
    char* theLastDeadStone;

    void resetMarkedGroupLists();
    void resetEmptyGroupLists();

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
