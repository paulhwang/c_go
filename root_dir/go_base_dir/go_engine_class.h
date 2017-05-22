/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_ENGINE_CLASS_H__
#define __GO_ENGINE_CLASS_H__

class GoGroupClass;
class GoGroupListClass;
class GoMoveClass;
#include "go_base_class.h"

#define GO_GROUP_LIST_ARRAY_SIZE 7

class GoEngineClass {
  public:
    GoEngineClass(GoBaseClass* base_object_val);
    ~GoEngineClass(void);

    char const* objectName(void);
    void resetEngineObjectData(void);
    GoBaseClass* baseObject(void);
    GoBoardClass* boardObject(void);

    void enterWar(GoMoveClass* move_val);

  private:
    GoBaseClass *theBaseObject;
    int theGroupListCount;
    GoGroupListClass* theGroupListArray[GO_GROUP_LIST_ARRAY_SIZE];
    int theBlackCaptureStones;
    int theWhiteCaptureStones;
    char* theCaptureCount;
    char* theLastDeadStone;

    void clearLastDeadStone(void);

    GoGroupClass* insertStoneToGroupList(GoMoveClass* move_val);
    int killOtherColorGroups(GoMoveClass* move_val, GoGroupClass* group_val);
    int killOtherColorGroup(GoGroupClass* group, int x_val, int y_val);
    void resetMarkedGroupLists(void);
    void resetEmptyGroupLists(void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
