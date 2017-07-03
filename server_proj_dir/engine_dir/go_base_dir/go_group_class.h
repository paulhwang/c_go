/*
  Copyrights reserved
  Written by Paul Hwang
  File name" go_group_class.h
*/

#pragma once

class GoGroupListClass;

class GoGroupClass {
    GoGroupListClass *theGroupListObject;
    int theMaxX;
    int theMinX;
    int theMaxY;
    int theMinY;
    int theDeadMatrix[19][19];
    int theIndexNumber;
    int theStoneCount;
    int theMyColor;
    int theHisColor;
    int theExistMatrix[19][19];

    void resetMarkedBoardObjectData();

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    GoGroupClass(GoGroupListClass *group_list_object_val);
    ~GoGroupClass() {}
    char const *objectName() {return "GoGroupClass";}

    GoGroupListClass *groupListObject(void) {return this->theGroupListObject;}
    void setGroupListObject(GoGroupListClass *group_list_val) {this->theGroupListObject = group_list_val;}
    int maxX(void) {return this->theMaxX;}
    int minX(void) {return this->theMinX;}
    int maxY(void) {return this->theMaxY;}
    int minY(void) {return this->theMinY;}
    int indexNumber(void) {return this->theIndexNumber;}
    void setIndexNumber(int val) {this->theIndexNumber = val;}
    int stoneCount(void) {return this->theStoneCount;}
    int myColor(void) {return this->theMyColor;}
    int hisColor(void) {return this->theHisColor;}
    int existMatrix(int x_val, int y_val) {return this->theExistMatrix[x_val][y_val];}

    void insertStoneToGroup(int x_val, int y_val, int dead_val);
    int isCandidateGroup(int x_val, int y_val);
    void mergeWithOtherGroup(GoGroupClass *group2);
    int groupHasAir(void);
    void removeDeadStoneFromBoard(void);
    void abendGroup(void);
    void abendOnGroupConflict(GoGroupClass *other_group_val);
};
