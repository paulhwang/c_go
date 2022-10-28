/*
  Copyrights reserved
  Written by Paul Hwang
  File name: session_class.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "session_class.h"

SessionClass::SessionClass (
    int debug_on_val,
    void *list_mgr_obj_val,
    LinkClass *link_obj_val)
        :ListEntryClass(list_mgr_obj_val)
{
    this->debugOn_ = true && debug_on_val;
    this->linkObj_ = link_obj_val;
    this->groupObj_ = 0;
    this->pendingDataQueue_ = phwangMallocQueue(0, this->objectName());

    if (true && this->debugOn_) {
        printf("SessionClass::SessionClass() new_session=%s\n", this->sessionIdIndex());
    }
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
