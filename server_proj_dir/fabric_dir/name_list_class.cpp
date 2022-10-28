/*
  Copyrights reserved
  Written by Paul Hwang
  File name: name_list_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "name_list_class.h"
#include "fabric_class.h"
#include "link_class.h"
#include "../define_dir/fe_def.h"
#include "../../phwang_dir/list_mgr_dir/list_mgr_class.h"

NameListClass::NameListClass (int debug_on_val, FabricClass *fabric_object_val)
{
    memset(this, 0, sizeof(*this));
    this->debugOn_ = true && debug_on_val;
    this->fabricObj_ = fabric_object_val;
    this->nameListTag_ = 0;

    phwangDebugS(false, "NameListClass::NameListClass", "init");
}

NameListClass::~NameListClass (void)
{
}

void NameListClass::updateNameList (void)
{
    void *link_list_mgr = this->fabricObj_->linkListMgrObject();

    int max_index = phwnagListMgrGetMaxIndex(link_list_mgr, "NameListClass::updateNameList()");
    LinkClass **link_entry_array = (LinkClass **) phwangListMgrGetEntryTableArray(link_list_mgr);
    char *ptr = this->nameList_;
    int name_len;
    int name_list_size = SIZE_DEF::NAME_LIST_TAG_SIZE;

    this->nameListTag_++;
    if (this->nameListTag_ > SIZE_DEF::NAME_LIST_TAG_MAX_VALUE) {
        this->nameListTag_ = 1;
    }

    for (int i = max_index; i >= 0; i--) {
        if (link_entry_array[i]) {
            if (ptr == this->nameList_) {
                phwangEncodeNumber(ptr, this->nameListTag_, SIZE_DEF::NAME_LIST_TAG_SIZE);
                ptr += SIZE_DEF::NAME_LIST_TAG_SIZE;
            }
            else {
                *ptr++ = ',';
            }
            *ptr++ = '"';
            name_len = strlen(link_entry_array[i]->myName());
            memcpy(ptr, link_entry_array[i]->myName(), name_len);
            ptr += name_len;
            *ptr++ = '"';
            name_list_size += (name_len + 3);
        }
    }
    *ptr = 0;

    if (name_list_size > SIZE_DEF::NAME_LIST_BUFFER_SIZE) {
        printf("name_list_size=%d\n", name_list_size);
        phwangAbendS("NameListClass::updateNameList", "buffer too small");
    }

    if (true && this->debugOn_) {
        printf("NameListClass::updateNameList() %s\n", this->nameList_);
    }
}

char *NameListClass::getNameList (int tag_val)
{
	if (this->nameListTag_ == tag_val) {
		return 0;
	}
	return this->nameList_;
}
