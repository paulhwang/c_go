/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_engine_class.h
*/

#pragma once

class GoGroupClass;
class GoGroupListClass;
class GoMoveClass;
#include "go_base_class.h"

#define GO_GROUP_LIST_ARRAY_SIZE 7

class GoEngineClass {
    GoBaseClass *theBaseObject;
    int theGroupListCount;
    GoGroupListClass* theGroupListArray[GO_GROUP_LIST_ARRAY_SIZE];
    int theBlackCaptureStones;
    int theWhiteCaptureStones;
    char* theCaptureCount;
    char* theLastDeadStone;

    GoGroupListClass* emptyGroupList(void);
    GoGroupListClass* blackGroupList(void);
    GoGroupListClass* whiteGroupList(void);
    GoGroupListClass* blackDeadGroupList(void);
    GoGroupListClass* whiteDeadGroupList(void);
    GoGroupListClass* blackEmptyGroupList(void);
    GoGroupListClass* whiteEmptyGroupList(void);
    void clearLastDeadStone(void);

    GoGroupClass* insertStoneToGroupList(GoMoveClass* move_val);
    int killOtherColorGroups(GoMoveClass* move_val, GoGroupClass* group_val);
    int killOtherColorGroup(GoGroupClass* group, int x_val, int y_val);
    void resetMarkedGroupLists(void);
    void resetEmptyGroupLists(void);
    void abendEngine(void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GoEngineClass(GoBaseClass* base_object_val);
    ~GoEngineClass(void);

    void enterWar(GoMoveClass* move_val);
    void resetEngineObjectData(void);

    GoBoardClass* boardObject(void);
    GoBaseClass* baseObject(void) {return theBaseObject;}
    char const* objectName(void) {return "GoEngineClass";}
};
