/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../../phwang_dir/malloc_dir/malloc_class.h"
#include "link_class.h"
#include "session_class.h"
#include "fabric_class.h"
#include "../define_dir/fe_command_define.h"
  
LinkClass::LinkClass (
    void *list_mgr_object_val,
    FabricClass *fabric_object_val,
    char const* link_name_val)
        :ListEntryClass(list_mgr_object_val)
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
    this->theSessionListMgrObject = phwangListMgrMalloc("SESSION", FE_CommandClass::SESSION_ID_SIZE, FE_CommandClass::SESSION_INDEX_SIZE, 300);
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

void LinkClass::freeSession(SessionClass *session_object_val)
{
    
}

SessionClass *LinkClass::searchSession (char *data_val)
{
    return (SessionClass *) phwangListMgrSearchEntry(this->theSessionListMgrObject, data_val, 0);
}

char *LinkClass::getPendingSessionSetup (void)
{
    return (char *) phwangDequeue(this->thePendingSessionSetupQueue, "LinkClass::getPendingSessionSetup()");
}

char *LinkClass::getPendingSessionSetup3 (void)
{
    return (char *) phwangDequeue(this->thePendingSessionSetupQueue3, "LinkClass::getPendingSessionSetup3()");
}

void LinkClass::setPendingSessionSetup (
    char *session_id_index_val,
    char *theme_data_val)
{
    char *buf, *data_ptr;

    buf = data_ptr = (char *) phwangMalloc(FE_CommandClass::FE_DL_DATA_BUF_SIZE, MallocClass::setPendingSessionSetup);
    memcpy(data_ptr, session_id_index_val, FE_CommandClass::SESSION_ID_INDEX_SIZE);
    data_ptr += FE_CommandClass::SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_data_val);
    phwangEnqueue(this->thePendingSessionSetupQueue, buf);
}

void LinkClass::setPendingSessionSetup3 (
    char *session_id_index_val,
    char const *theme_data_val)
{
    char *buf, *data_ptr;

    buf = data_ptr = (char *) phwangMalloc(FE_CommandClass::FE_DL_DATA_BUF_SIZE, MallocClass::setPendingSessionSetup3);
    memcpy(data_ptr, session_id_index_val, FE_CommandClass::SESSION_ID_INDEX_SIZE);
    data_ptr += FE_CommandClass::SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_data_val);
    phwangEnqueue(this->thePendingSessionSetupQueue3, buf);
}
