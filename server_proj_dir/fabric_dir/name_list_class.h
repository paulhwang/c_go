/*
  Copyrights reserved
  Written by Paul Hwang
  File name: name_list_class.h
*/

#pragma once

class FabricClass;

class NameListClass {
#define NAME_LIST_CLASS_NAME_LIST_BUFFER_SIZE 10240

    char theObjectName[64];
    FabricClass *fabricObject_;
    int nameListTag_;
    char nameList_[NAME_LIST_CLASS_NAME_LIST_BUFFER_SIZE + 4];

public:
    NameListClass(FabricClass *fabric_object_val);
    ~NameListClass(void);
    char *objectName(void) {return this->theObjectName;}

    int nameListTag(void) {return this->nameListTag_;}

    void updateNameList(void);
    char *getNameList(int tag_val);
};
