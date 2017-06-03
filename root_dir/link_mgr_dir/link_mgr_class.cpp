/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.cpp
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../../utils_dir/logit.h"
#include "../../utils_dir/encode.h"
#include "../../utils_dir/queue_mgr_class.h"
#include "../main_dir/main_exports.h"
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
    if (this->theGlobalLinkId >= LINK_MGR_MAX_GLOBAL_LINK_ID) {
        this->theGlobalLinkId = 0;
    }
    this->theGlobalLinkId++;
    return this->theGlobalLinkId;
}

int LinkMgrClass::allocLinkIndex (void)
{
    int index = 0;
    while (index < LINK_MGR_LINK_ARRAY_SIZE) {
        if (!this->theLinkTableArray[index]) {
            return index;
        }
        index++;
    }
    return -1;
}

void LinkMgrClass::mallocLink (char const *data_val)
{
    if (1) {
        this->logit("mallocLink", data_val);
    }
    int link_id = this->allocLinkId();
    int link_index = this->allocLinkIndex();
    if (link_index != -1) {
        this->theLinkTableArray[link_index] = new LinkClass(this, link_id, link_index, data_val);

        char *data_buf = (char *) malloc(LINK_MGR_DATA_BUFFER_SIZE + 4);
        data_buf[0] = LINK_MGR_PROTOCOL_RESPOND_IS_MALLOC_LINK;
        encodeIdIndex(data_buf + 1, link_id, LINK_MGR_PROTOCOL_LINK_ID_SIZE, link_index, LINK_MGR_PROTOCOL_LINK_INDEX_SIZE);

        this->transmitData(data_buf);
    }
    else {
        /* TBD */
    }

/*
    int link_index = allocLinkIndex();
    LinkClass *link = new LinkClass(this, this->allocLinkId(), link_index, my_name_val);
    if (!link) {
        return 0;
    }

    return link;
    */
}

void LinkMgrClass::transmitData(char *data_val)
{
    if (1) {
        this->logit("transmitData", data_val);
        mainTransmitDataToTransport(this->theMainObject, data_val);
    }
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

