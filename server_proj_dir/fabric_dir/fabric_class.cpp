/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "fabric_class.h"
#include "u_fabric_dir/u_fabric_class.h"
#include "d_fabric_dir/d_fabric_class.h"
#include "group_mgr_dir/group_mgr_class.h"
#include "link_mgr_dir/link_mgr_class.h"

FabricClass::FabricClass (void)
{
    memset(this, 0, sizeof(FabricClass));
    this->theLinkMgrObject = new LinkMgrClass(this);
    this->theGroupMgrObject = new GroupMgrClass(this);
    this->theUFabricObject = new UFabricClass(this);
    this->theDFabricObject = new DFabricClass(this);

    if (1) {
        this->logit("FabricClass", "init");
    }
}

FabricClass::~FabricClass (void)
{
    this->theGroupMgrObject->~GroupMgrClass(); 
    this->theLinkMgrObject->~LinkMgrClass(); 
}

void FabricClass::logit (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void FabricClass::abend (char const* str0_val, char const* str1_val)
{
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
