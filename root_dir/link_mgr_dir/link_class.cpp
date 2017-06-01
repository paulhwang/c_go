/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_class.cpp
*/

#include <stdio.h>
#include <string.h>
#include "link_class.h"
#include "link_mgr_class.h"
#include "../../utils_dir/logit.h"

LinkClass::LinkClass (LinkMgrClass *link_mgr_object_val, int link_id_val, char const* link_name_val)
{
    memset(this, 0, sizeof(LinkClass));
    this->theLinkMgrObject = link_mgr_object_val;
    this->theLinkId = link_id_val;
    if (strlen(link_name_val) <= LINK_CLASS_LINK_NAME_BUF_SIZE) {
        strcpy(this->theLinkName, link_name_val);
    }
    else {
        memcpy(this->theLinkName, link_name_val, LINK_CLASS_LINK_NAME_BUF_SIZE);
        this->theLinkName[LINK_CLASS_LINK_NAME_BUF_SIZE] = 0;
    }

    if (1) {
        this->logit("LinkClass", "init");
    }
}

LinkClass::~LinkClass (void)
{
}

void LinkClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theLinkMgrObject->linkMgrLogit(s, str1_val);
}

void LinkClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->theLinkMgrObject->linkMgrAbend(s, str1_val);
}
