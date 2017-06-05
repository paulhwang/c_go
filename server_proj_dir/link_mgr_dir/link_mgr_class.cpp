/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/tp_dir/tp_server_class.h"
#include "../../phwang_dir/tp_dir/tp_transfer_class.h"
#include "link_mgr_class.h"
#include "link_class.h"

LinkMgrClass::LinkMgrClass (MainClass *main_object_val)
{
    memset(this, 0, sizeof(LinkMgrClass));
    this->theMainObject = main_object_val;
    this->theTpServerObject = new TpServerClass(this);
    this->theGlobalLinkId = 0;

    this->theReceiveQueue = phwangMallocQueue(LINK_MGR_RECEIVE_QUEUE_SIZE);

    if (1) {
        this->logit("LinkMgrClass", "init");
    }
}

LinkMgrClass::~LinkMgrClass (void)
{
    phwangFreeQueue(this->theReceiveQueue);
    this->theTpTransferObject->~TpTransferClass(); 
    this->theTpServerObject->~TpServerClass(); 
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
        phwangEncodeIdIndex(data_buf + 1, link_id, LINK_MGR_PROTOCOL_LINK_ID_SIZE, link_index, LINK_MGR_PROTOCOL_LINK_INDEX_SIZE);

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
        this->theTpTransferObject->exportTransmitData(data_val);
    }
}

void LinkMgrClass::freeLink (LinkClass *link_object_val)
{
    if (!link_object_val) {
        return;
    }
    link_object_val->~LinkClass();
}

void LinkMgrClass::linkMgrLogit (char const* str0_val, char const* str1_val) {
    phwangLogit(str0_val, str1_val);
}

void LinkMgrClass::linkMgrAbend (char const* str0_val, char const* str1_val) {
    phwangAbend(str0_val, str1_val);
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

