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
#include "../define_dir/size_def.h"
#include "../define_dir/fe_def.h"
#include "../define_dir/fabric_def.h"
  
LinkClass::LinkClass (
    void *list_mgr_object_val,
    FabricClass *fabric_object_val,
    char const* my_name_val,
    char device_type_val,
    void *port_object_val)
        :ListEntryClass(list_mgr_object_val)
{
    this->fabricObject_ = fabric_object_val;
    this->myName_ = (char *) phwangMalloc(strlen(my_name_val) + 1, MallocClass::LinkClass);
    strcpy(this->myName_, my_name_val);
    this->deviceType_ = device_type_val;
    this->portObject_ = port_object_val;
    this->theNameListChanged = 'D';

    this->sessionListMgrObject_ = phwangListMgrMalloc("SESSION", SIZE_DEF::SESSION_ID_SIZE, SIZE_DEF::SESSION_INDEX_SIZE, SIZE_DEF::SESSION_ID_INITIAL_VALUE);
    this->resetKeepAliveTime();
    this->thePendingSessionSetupQueue = phwangMallocQueue(0, this->objectName());
    this->thePendingSessionSetupQueue3 = phwangMallocQueue(0, this->objectName());

    phwangDebugSSS(true, "LinkClass::LinkClass", "myName=", this->myName(),this->linkIdIndex());
}

LinkClass::~LinkClass (void)
{
    phwangFreeQueue(this->thePendingSessionSetupQueue, "LinkClass::~LinkClass(1)");
    phwangFreeQueue(this->thePendingSessionSetupQueue3, "LinkClass::~LinkClass(3)");
    phwangFree(this->myName_);
}

SessionClass *LinkClass::mallocSession (void)
{
    SessionClass *session = new SessionClass(this->sessionListMgrObject_, this);
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
    return (SessionClass *) phwangListMgrSearchEntry(this->sessionListMgrObject_, data_val, 0);
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
    char theme_type_val,
    char *theme_data_val)
{
    char *buf = (char *) phwangMalloc(FABRIC_DEF::FE_PENDING_SESSIONS_SIZE, MallocClass::setPendingSessionSetup);
    char *current_ptr = buf;

    memcpy(current_ptr, session_id_index_val, SIZE_DEF::SESSION_ID_INDEX_SIZE);
    current_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;

    *current_ptr++ = theme_type_val;

    strcpy(current_ptr, theme_data_val);

    phwangEnqueue(this->thePendingSessionSetupQueue, buf);
}

void LinkClass::setPendingSessionSetup3 (
    char *session_id_index_val,
    char const *theme_data_val)
{
    char *buf, *data_ptr;

    buf = data_ptr = (char *) phwangMalloc(FABRIC_DEF::FE_PENDING_SESSIONS_SIZE, MallocClass::setPendingSessionSetup3);
    memcpy(data_ptr, session_id_index_val, SIZE_DEF::SESSION_ID_INDEX_SIZE);
    data_ptr += SIZE_DEF::SESSION_ID_INDEX_SIZE;
    strcpy(data_ptr, theme_data_val);
    phwangEnqueue(this->thePendingSessionSetupQueue3, buf);
}
