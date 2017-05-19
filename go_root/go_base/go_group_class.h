/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_GROUP_CLASS_H__/*
  Copyrights reserved
  Written by Paul Hwang
*/

#ifndef __GO_BOARD_CLASS_H__
#define __GO_BOARD_CLASS_H__

class GoBaseClass;

class GoGroupClass {
  public:
    GoGroupClass(GoBaseClass* the_base_object);
    ~GoGroupClass();

    char const* objectName();
    GoBaseClass* baseObject();

    void resetMarkedBoardObjectData();

  private:
    GoBaseClass *theBaseObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif

#define __GO_GROUP_CLASS_H__

class go_base_class;

class go_group_class {
  public:
    go_group_class(go_base_class* the_base_object);
    ~go_group_class();

    char const* object_name();
    go_base_class* base_object();

  private:
    go_base_class *the_base_object;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
};

#endif
