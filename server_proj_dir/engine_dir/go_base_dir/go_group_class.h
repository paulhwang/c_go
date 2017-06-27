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
    int theExistMatrix[19][19];
    int theDeadMatrix[19][19];
    int theIndexNumber;
    int theMaxX;
    int theMinX;
    int theMaxY;
    int theMinY;
    int theStoneCount;
    char theMyColor;
    char theHisColor;

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

protected:
    friend GoFightClass;

    int stoneCount(void) {return this->theStoneCount;}
    int myColor(void) {return this->theMyColor;}
    int hisColor(void) {return this->theHisColor;}

    void insertStoneToGroup(int x_val, int y_val, int dead_val);
    int groupHasAir(void);

public:
    GoGroupClass(GoGroupListClass *group_list_object_val);
    ~GoGroupClass() {}
    char const* objectName() {return "GoGroupClass";}

    GoGroupListClass* groupListObject();
    void setGroupListObject(GoGroupListClass* group_list_val);
    GoBaseClass* baseObject();

    void setIndexNumber(int val);
    int isCandidateGroup(int x_val, int y_val);
    void resetMarkedBoardObjectData();
};
