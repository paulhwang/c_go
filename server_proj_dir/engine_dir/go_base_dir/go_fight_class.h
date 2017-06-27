/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_engine_class.h
*/

#pragma once

class GoBaseClass;
class GoGroupClass;
class GoGroupListClass;
class GoMoveClass;

class GoFightClass {
#define GO_FIGHT_CLASS_GROUP_LIST_ARRAY_SIZE 7
    GoBaseClass *theBaseObject;
    GoGroupListClass *theGroupListArray[GO_FIGHT_CLASS_GROUP_LIST_ARRAY_SIZE];
    char *theCaptureCount;
    char *theLastDeadStone;

    GoGroupListClass* emptyGroupList(void);
    GoGroupListClass* blackGroupList(void);
    GoGroupListClass* whiteGroupList(void);
    GoGroupListClass* blackDeadGroupList(void);
    GoGroupListClass* whiteDeadGroupList(void);
    GoGroupListClass* blackEmptyGroupList(void);
    GoGroupListClass* whiteEmptyGroupList(void);
    void clearLastDeadStone(void);


    void resetEngineObjectData(void);
    GoGroupClass *insertStoneToGroupList(GoMoveClass *move_val);
    int killOtherColorGroups(GoMoveClass *move_val, GoGroupClass *group_val);
    int killOtherColorGroup(GoGroupClass *group, int x_val, int y_val);
    void resetMarkedGroupLists(void);
    void resetEmptyGroupLists(void);
    void abendEngine(void);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

protected:
    friend class GoGameClass;
    friend class GoGroupListClass;

    GoBaseClass *baseObject(void) {return this->theBaseObject;}
    void enterBattle(GoMoveClass *move_val);

public:
    GoFightClass(GoBaseClass *base_object_val);
    ~GoFightClass(void) {}
    char const *objectName(void) {return "GoFightClass";}
};
