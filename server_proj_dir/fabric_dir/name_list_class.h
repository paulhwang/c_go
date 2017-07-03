/*
  Copyrights reserved
  Written by Paul Hwang
  File name: name_list_class.h
*/

#pragma once

class FabricClass;

class NameListClass {
#define NAME_LIST_CLASS_NAME_LIST_BUFFER_SIZE 1024

    FabricClass *theFabricObject;
    int theNameListIndex;
    char theNameList[NAME_LIST_CLASS_NAME_LIST_BUFFER_SIZE + 4];

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class FabricClass;

    void updateNameList(void);
    //char *nameList(void);

public:
    NameListClass(FabricClass *fabric_object_val);
    ~NameListClass(void);
    char const* objectName(void) {return "NameListClass";}
};
