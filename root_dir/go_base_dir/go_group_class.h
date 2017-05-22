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
    GoBaseClass* baseObject();

    void setIndexNumber(int val);
    void insertStoneToGroup(int x_val, int y_val, int dead_val);
    int isCandidateGroup(int x_val, int y_val);
    void resetMarkedBoardObjectData();

  private:
    GoGroupListClass *theGroupListObject;
    int theIndexNumber;

    int indexNumber(void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};
#endif
