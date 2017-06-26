/*
  Copyrights reserved
  Written by Paul Hwang
  File name" go_group_class.h
*/

#pragma once
#include "go_base_class.h"

class GoGroupListClass;

class GoGroupClass {
    GoGroupListClass *theGroupListObject;
    int theIndexNumber;
    int theMaxX;
    int theMinX;
    int theMaxY;
    int theMinY;

    int indexNumber(void);
    int maxX (void);
    int minX (void);
    int maxY (void);
    int minY (void);
    void setMaxX(int val);
    void setMinX(int val);
    void setMaxY(int val);
    void setMinY(int val);

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    GoGroupClass(GoGroupListClass* group_list_object_var);
    ~GoGroupClass() {}
    char const* objectName() {return "GoGroupClass";}

    GoGroupListClass* groupListObject();
    void setGroupListObject(GoGroupListClass* group_list_val);
    GoBaseClass* baseObject();

    void setIndexNumber(int val);
    void insertStoneToGroup(int x_val, int y_val, int dead_val);
    int isCandidateGroup(int x_val, int y_val);
    int groupHasAir(void);
    void resetMarkedBoardObjectData();
};
