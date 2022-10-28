/*
  Copyrights reserved
  Written by Paul Hwang
  File name: name_list_class.h
*/

#pragma once

#include "../define_dir/size_def.h"
#include "fabric_class.h"

class FabricClass;

class NameListClass {
    int debugOn_;
    FabricClass *fabricObj_;
    int nameListTag_;
    char nameList_[SIZE_DEF::NAME_LIST_BUFFER_SIZE + 4];

public:
    NameListClass(int debug_on_val, FabricClass *fabric_object_val);
    ~NameListClass(void);
    char *objectName(void) {return "NameListClass";}

    int nameListTag(void) {return this->nameListTag_;}

    void updateNameList(void);
    char *getNameList(int tag_val);
};
