/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "session_class.h"

SessionClass::SessionClass (
    void *list_mgr_obj_val,
    LinkClass *link_obj_val)
        :ListEntryClass(list_mgr_obj_val)
{
    this->linkObj_ = link_obj_val;
    this->groupObj_ = 0;
    this->pendingDataQueue_ = phwangMallocQueue(0, this->objectName());

    phwangDebugSS(true, "SessionClass::SessionClass", "new_session:", this->sessionIdIndex());
}

SessionClass::~SessionClass (void)
{
    phwangFreeQueue(this->pendingDataQueue_, "SessionClass::~SessionClass()");
}

void SessionClass::enqueuePendingData (char *data_val)
{
    char *buf = (char *) malloc(strlen(data_val) + 4);
    strcpy(buf, data_val);
    phwangEnqueue(this->pendingDataQueue_, buf);
}

char *SessionClass::dequeuePendingData (void)
{
    return (char *) phwangDequeue(this->pendingDataQueue_, "SessionClass::getPendingDownLinkData()");
}
