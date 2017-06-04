/*
  Copyrights reserved
  Written by Paul Hwang
  File name" go_group_class.h
*/

#ifndef __GO_GROUP_CLASS_H__
#define __GO_GROUP_CLASS_H__

class GoGroupListClass;
#include "go_base_class.h"

class GoGroupClass {
  public:
    GoGroupClass(GoGroupListClass* group_list_object_var);
    ~GoGroupClass();

    char const* objectName();
    GoGroupListClass* groupListObject();
    void setGroupListObject(GoGroupListClass* group_list_val);
    GoBaseClass* baseObject();

    void setIndexNumber(int val);
    void insertStoneToGroup(int x_val, int y_val, int dead_val);
    int isCandidateGroup(int x_val, int y_val);
    int groupHasAir(void);
    void resetMarkedBoardObjectData();

  private:
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

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
