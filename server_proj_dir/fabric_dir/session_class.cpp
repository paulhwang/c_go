/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "session_class.h"

SessionClass::SessionClass (
    void *list_mgr_object_val,
    LinkClass *link_object_val)
        :ListEntryClass(list_mgr_object_val)
{
    this->linkObject_ = link_object_val;
    this->groupObject_ = 0;
    this->pendingDownLinkDataQueue_ = phwangMallocQueue(0, this->objectName());

    phwangDebugSS(true, "SessionClass::SessionClass", "new_session:", this->sessionIdIndex());
}

SessionClass::~SessionClass (void)
{
    phwangFreeQueue(this->pendingDownLinkDataQueue_, "SessionClass::~SessionClass()");
}

void SessionClass::enqueuePendingDownLinkData (char *data_val)
{
    char *buf = (char *) malloc(strlen(data_val) + 4);
    strcpy(buf, data_val);
    phwangEnqueue(this->pendingDownLinkDataQueue_, buf);
}

char *SessionClass::getPendingDownLinkData (void)
{
    return (char *) phwangDequeue(this->pendingDownLinkDataQueue_, "SessionClass::getPendingDownLinkData()");
}
