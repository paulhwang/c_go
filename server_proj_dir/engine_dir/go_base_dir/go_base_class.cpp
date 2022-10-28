/*
  Copyrights reserved
  Written by Paul Hwang
  File name: go_base_class.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "go_base_class.h"
#include "../engine_class.h"

GoBaseClass::GoBaseClass (
    int debug_on_val,
    void *list_mgr_object_val,
    EngineClass *engine_object_val,
    char *config_info_val):
    ListEntryClass(list_mgr_object_val),
    theEngineObject(engine_object_val)
{
    this->debugOn_ = true && debug_on_val;
    this->theConfigObject = new GoConfigClass(this->debugOn_, this, config_info_val);
    this->theBoardObject = new GoBoardClass(this->debugOn_, this);
    this->theFightObject = new GoFightClass(this->debugOn_, this);
    this->thePortObject = new GoPortClass(this->debugOn_, this);
    this->theGameObject = new GoGameClass(this->debugOn_, this);

    if (true && this->debugOn_) {
        printf("GoBaseClass::GoBaseClass() new_go_base=%s\n", this->goBaseIdIndex());
    }
}

GoBaseClass::~GoBaseClass (void)
{
    this->theConfigObject->~GoConfigClass();
    this->theBoardObject->~GoBoardClass();
    this->theFightObject->~GoFightClass();
    this->thePortObject->~GoPortClass();
    this->theGameObject->~GoGameClass();
}
