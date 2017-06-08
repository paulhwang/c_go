/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "link_mgr_class.h"
#include "link_class.h"

void linkMgrTransportServerAcceptConnection (void *link_mgr_object_val, void *tp_transfer_object_val) {
    //phwangLogit("Golbal::linkMgrTransportServerAcceptConnection", ((LinkMgrClass *) link_mgr_object_val)->objectName());
    //phwangLogit("Golbal::linkMgrTransportServerAcceptConnection", ((TpTransferClass *) tp_transfer_object_val)->objectName());
    ((LinkMgrClass *) link_mgr_object_val)->exportAcceptConnection(tp_transfer_object_val);
}

void linkMgrReceiveDataFromTransport (void *link_mgr_object_val, void *data_val) {
    phwangLogit("Golbal::linkMgrReceiveDataFromTransport", (char *) data_val);
    ((LinkMgrClass *) link_mgr_object_val)->exportReceiveData(data_val);
}

LinkMgrClass::LinkMgrClass (void *main_object_val)
{
    memset(this, 0, sizeof(LinkMgrClass));
    this->theMainObject = main_object_val;
    this->theTpServerObject = phwangMallocTpServer(this, LINK_MGR_PROTOCOL_TRANSPORT_PORT_NUMBER, linkMgrTransportServerAcceptConnection, this, linkMgrReceiveDataFromTransport, this);
    this->theGlobalLinkId = 0;

    this->theReceiveQueue = phwangMallocQueue(LINK_MGR_RECEIVE_QUEUE_SIZE);

    if (1) {
        this->logit("LinkMgrClass", "init");
    }
}

LinkMgrClass::~LinkMgrClass (void)
{
    phwangFreeTpServer(this->theTpServerObject); 
    phwangFreeTpTransfer(this->theTpTransferObject); 
    phwangFreeQueue(this->theReceiveQueue);
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

void LinkMgrClass::mallocSession (char *data_val)
{
    int link_id;
    int link_id_index;
    if (1) {
        this->logit("mallocSession", data_val);
    }

    phwangDecodeIdIndex(data_val,
                &link_id,
                LINK_MGR_PROTOCOL_LINK_ID_SIZE,
                &link_id_index,
                LINK_MGR_PROTOCOL_LINK_INDEX_SIZE);
    data_val += LINK_MGR_PROTOCOL_LINK_ID_INDEX_SIZE;

    if (1) {
        char s[LOGIT_BUF_SIZE];
        sprintf(s, "link_id=%d link_index-%d", link_id, link_id_index);
        this->logit("mallocSession", s);
    }
}

void LinkMgrClass::transmitData(char *data_val)
{
    if (1) {
        this->logit("transmitData", data_val);
        phwangTpTransmit(this->theTpTransferObject, data_val);
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

