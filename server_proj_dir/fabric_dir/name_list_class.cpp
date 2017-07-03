/*
  Copyrights reserved
  Written by Paul Hwang
  File name: name_list_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "name_list_class.h"
#include "fabric_class.h"
  
NameListClass::NameListClass (FabricClass *fabric_object_val):
	theFabricObject(fabric_object_val),
    theNameListIndex(0)
{

    this->debug(true, "NameListClass", "init");
}

NameListClass::~NameListClass (void)
{
}

void NameListClass::updateNameList(void)
{
    void *link_list_mgr = this->theFabricObject->linkListMgrObject();
    int max_index = 0;
    LinkClass **link_entry_array;

    for (int i = 0 ; i < max_index; i++) {
        //if (!link_entry_array[i]) {
        //}
    }

	this->theNameListIndex++;
}

char *NameListClass::getNameList(int index_val)
{
	if (this->theNameListIndex == index_val) {
		return 0;
	}
	return this->theNameList;
}

void NameListClass::logit (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangLogit(s, str1_val);
}

void NameListClass::abend (char const *str0_val, char const *str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    phwangAbend(s, str1_val);
}
