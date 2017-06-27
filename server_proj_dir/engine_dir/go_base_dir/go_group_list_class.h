/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_group_list_class.h
*/

#pragma once
#include "go_base_class.h"
#include "go_fight_class.h"

class GoGroupListClass
{
    GoFightClass *theEngineObject;
    int theGroupCount;
    GoGroupClass *theListArray[400];

    int groupCount(void);
    void incrementGroupCount(void);
    void decrementGroupCount(void);
    GoGroupClass* listArray(int index_val);
    void setListArray(int index_val, GoGroupClass* data_val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

protected:
    friend class GoFightClass;

    void removeGroupFromGroupList(GoGroupClass *group_val);

public:
    GoGroupListClass(GoFightClass* engine_val,
                       int index_val,
                       int color_val,
                       int dead_val,
                       char const* big_stone_val,
                       char const* small_stone_val);
    ~GoGroupListClass(void);
    char const* objectName(void) {return "GoGroupListClass";}
 
    GoFightClass *fightObject(void) {return this->theEngineObject;}
    GoBaseClass* baseObject(void) {return this->theEngineObject->baseObject();}


    void insertGroupToGroupList(GoGroupClass* group_val);
    GoGroupClass* findCandidateGroup(int x_val, int y_val);
};
