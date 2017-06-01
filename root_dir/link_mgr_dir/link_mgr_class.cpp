/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.cpp
*/

#include <stdio.h>
#include <string.h>
#include "../../utils_dir/logit.h"
#include "../../utils_dir/queue_mgr_class.h"
#include "link_mgr_class.h"
#include "link_class.h"

LinkMgrClass::LinkMgrClass (void *main_object_val)
{
    memset(this, 0, sizeof(LinkMgrClass));
    this->theMainObject = main_object_val;
    this->theGlobalLinkId = 0;

    this->theReceiveQueue = new QueueMgrClass();
    this->theReceiveQueue->initQueue(LINK_MGR_RECEIVE_QUEUE_SIZE);

    if (1) {
        this->logit("LinkMgrClass", "init");
    }
}

LinkMgrClass::~LinkMgrClass (void)
{
    delete this->theReceiveQueue;
}

int LinkMgrClass::allocLinkId (void)
{
    this->theGlobalLinkId++;
    return this->theGlobalLinkId;
}

LinkClass *LinkMgrClass::mallocLink (char const *my_name_val)
{
    int link_index = 0;
    LinkClass *link = new LinkClass(this, this->allocLinkId(), link_index, my_name_val);
    if (!link) {
        return 0;
    }

    return link;
}

void LinkMgrClass::freeLink (LinkClass *link_object_val)
{
    if (!link_object_val) {
        return;
    }
    this->linkTableArray[link_object_val->linkIndex()] = 0;
    link_object_val->~LinkClass();
}

void LinkMgrClass::linkMgrLogit (char const* str0_val, char const* str1_val) {
    LOGIT(str0_val, str1_val);
}

void LinkMgrClass::linkMgrAbend (char const* str0_val, char const* str1_val) {
    LOGIT(str0_val, str1_val);
}

void LinkMgrClass::logit (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->linkMgrLogit(s, str1_val);
}

void LinkMgrClass::abend (char const* str0_val, char const* str1_val) {
    char s[LOGIT_BUF_SIZE];
    sprintf(s, "%s::%s", this->objectName(), str0_val);
    this->linkMgrAbend(s, str1_val);
}

