/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_group_list_class.h
*/

#pragma once

class GoFightClass;

class GoGroupListClass
{
#define GO_GROUP_LIST_CLASS_GROUP_ARRAY_SIZE 400
    GoFightClass *theFightObject;
    int theIndexNumber;
    int theMyColor;
    int theHisColor;
    int theIsDead;
    char const *theBigStoneColor;
    char const *theSmallStoneColor;
    int theIsMarkedDead;
    int theGroupCount;
    GoGroupClass *theGroupArray[GO_GROUP_LIST_CLASS_GROUP_ARRAY_SIZE];

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

protected:
    friend class GoFightClass;
    friend class GoGroupClass;

    int totalStoneCount(void);
    GoFightClass *fightObject(void) {return this->theFightObject;}
    void insertGroupToGroupList(GoGroupClass *group_val);
    void removeGroupFromGroupList(GoGroupClass *group_val);
    GoGroupClass *findCandidateGroup(int x_val, int y_val);
    GoGroupClass *findOtherCandidateGroup(GoGroupClass *group_val, int x_val, int y_val);
    int stoneExistWithinMe(int x_val, int y_val);
    void abendGroupList(void);

public:
    GoGroupListClass(GoFightClass *fight_object_val,
                       int index_val,
                       int color_val,
                       int dead_val,
                       char const *big_stone_val,
                       char const *small_stone_val);
    ~GoGroupListClass(void);
    char const *objectName(void) {return "GoGroupListClass";}
};
