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
    this->theLinkObject = link_object_val;
    this->theGroupObject =0;
    this->thePendingDownLinkDataQueue = phwangMallocQueue(0, this->objectName());

    phwangDebugSS(true, "SessionClass::SessionClass", "new_session:", this->sessionIdIndex());
}

SessionClass::~SessionClass (void)
{
    phwangFreeQueue(this->thePendingDownLinkDataQueue, "SessionClass::~SessionClass()");
}

void SessionClass::enqueuePendingDownLinkData(char *data_val)
{
    char *buf = (char *) malloc(strlen(data_val) + 4);
    strcpy(buf, data_val);
    phwangEnqueue(this->thePendingDownLinkDataQueue, buf);
}
