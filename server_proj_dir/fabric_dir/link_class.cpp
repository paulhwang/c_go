/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "link_class.h"
#include "session_class.h"
#include "fabric_class.h"
#include "../protocol_dir/fe_command_class.h"
  
LinkClass::LinkClass (void *list_mgr_object_val, FabricClass *fabric_object_val, char const* link_name_val):
        ListEntryClass(list_mgr_object_val)
{
    this->theFabricObject = fabric_object_val;
    this->theNameListChanged = 'D';

    if (strlen(link_name_val) <= LINK_CLASS_LINK_NAME_BUF_SIZE) {
        strcpy(this->theLinkName, link_name_val);
    }
    else {
        memcpy(this->theLinkName, link_name_val, LINK_CLASS_LINK_NAME_BUF_SIZE);
        this->theLinkName[LINK_CLASS_LINK_NAME_BUF_SIZE] = 0;
    }
    this->theSessionListMgrObject = phwangListMgrMalloc("SESSION", SESSION_MGR_PROTOCOL_SESSION_ID_SIZE, SESSION_MGR_PROTOCOL_SESSION_INDEX_SIZE, 300);
    this->resetKeepAliveTime();
    this->thePendingSessionSetupQueue = phwangMallocQueue(0, this->objectName());
    this->thePendingSessionSetupQueue3 = phwangMallocQueue(0, this->objectName());

    phwangDebugSSS(true, "LinkClass::LinkClass", "new_link:", this->theLinkName, this->linkIdIndex());
}

LinkClass::~LinkClass (void)
{
    phwangFreeQueue(this->thePendingSessionSetupQueue, "LinkClass::~LinkClass(1)");
    phwangFreeQueue(this->thePendingSessionSetupQueue3, "LinkClass::~LinkClass(3)");
}

SessionClass *LinkClass::mallocSession (void)
{
    SessionClass *session = new SessionClass(this->theSessionListMgrObject, this);
    if (!session) {
        phwangAbendS("LinkClass::mallocSession", "fail_to_malloc_session");
        return 0;
    }
    return session;
}

void LinkClass::setPendingSessionSetup (char *session_id_index_val, char *theme_data_val)
{
    char *buf, *data_ptr;

    buf = data_ptr = (char *) malloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE);
    memcpy(data_ptr, session_id_index_val, SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_data_val);
    phwangEnqueue(this->thePendingSessionSetupQueue, buf);
}

void LinkClass::setPendingSessionSetup3 (char *session_id_index_val, char const *theme_data_val)
{
    char *buf, *data_ptr;

    buf = data_ptr = (char *) malloc(FECommandClass::DOWNLINK_DATA_BUFFER_SIZE);
    memcpy(data_ptr, session_id_index_val, SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE);
    data_ptr += SESSION_MGR_PROTOCOL_SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_data_val);
    phwangEnqueue(this->thePendingSessionSetupQueue3, buf);
}
