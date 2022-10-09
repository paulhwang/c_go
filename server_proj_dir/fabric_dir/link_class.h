/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_class.h
*/

#pragma once
#include <time.h>
#include "../../phwang_dir/list_mgr_dir/list_entry_class.h"

class SessionClass;
class FabricClass;

class LinkClass : public ListEntryClass {
#define LINK_CLASS_LINK_NAME_BUF_SIZE 32
#define LINK_CLASS_KEEP_ALIVE_TIMEOUT 60
private:
    FabricClass *fabricObject_;
    char *myName_;
    char deviceType_;
    void *portObject_;
    void *sessionListMgrObject_;
    void *pendingSessionSetupQueue2_;
    void *pendingSessionSetupQueue3_;
    char theNameListChanged;
    time_t theKeepAliveTime;

public:
    LinkClass (
        void *list_mgr_object_val,
        FabricClass *fabric_object_val,
        char const* my_name_val,
        char device_type_val,
        void *port_object_val);
    ~LinkClass(void);
    char const *objectName(void) {return "LinkClass";}

    char deviceType(void) {return this->deviceType_;}
    void *portObject(void) {return this->portObject_;}
    char *myName(void) {return this->myName_;}
    char *linkIdIndex(void) {return this->entryIdIndex();}
    time_t keepAliveTime(void) {return this->theKeepAliveTime;}

    SessionClass *mallocSession(void);
    void freeSession(SessionClass *session_object_val);
    void *sessionListMgrObject(void) {return this->sessionListMgrObject_;}
    SessionClass *searchSession(char *data_val);
    char *getPendingSessionSetup2(void);
    char *getPendingSessionSetup3(void);
    void setPendingSessionSetup2(
        char *session_id_index_val,
        char theme_type_val,
        char *theme_data_val);
    void setPendingSessionSetup3(char *session_id_index_val);
    void resetKeepAliveTime(void) {this->theKeepAliveTime = time((time_t *) 0);}
    int keepAliveTimerExpired(void) {return (time((time_t *) 0) - this->theKeepAliveTime) > LINK_CLASS_KEEP_ALIVE_TIMEOUT;}
};
