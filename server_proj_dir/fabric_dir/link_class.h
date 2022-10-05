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
    char *theMyName;
    char deviceType_;
    void *thePortObject;
    void *theSessionListMgrObject;
    void *thePendingSessionSetupQueue;
    void *thePendingSessionSetupQueue3;
    void *ajaxIdQueue_;
    char theNameListChanged;
    time_t theKeepAliveTime;

public:
    LinkClass (
        void *list_mgr_object_val,
        FabricClass *fabric_object_val,
        char const* link_name_val,
        char device_type_val,
        void *port_object_val);
    ~LinkClass(void);
    char const *objectName(void) {return "LinkClass";}

    char deviceType(void) {return this->deviceType_;}
    void *portObject(void) {return this->thePortObject;}
    char *myName(void) {return this->theMyName;}
    char *linkIdIndex(void) {return this->entryIdIndex();}
    time_t keepAliveTime(void) {return this->theKeepAliveTime;}

    SessionClass *mallocSession(void);
    void freeSession(SessionClass *session_object_val);
    void *sessionListMgrObject(void) {return this->theSessionListMgrObject;}
    SessionClass *searchSession(char *data_val);
    char *getAjaxId(void);
    void putAjaxId(char *ajax_id_val);
    char *getPendingSessionSetup(void);
    char *getPendingSessionSetup3(void);
    void setPendingSessionSetup(
        char *session_id_index_val,
        char theme_type_val,
        char *topic_data_val);
    void setPendingSessionSetup3(char *session_id_index_val, char const *topic_data_val);
    void resetKeepAliveTime(void) {this->theKeepAliveTime = time((time_t *) 0);}
    int keepAliveTimerExpired(void) {return (time((time_t *) 0) - this->theKeepAliveTime) > LINK_CLASS_KEEP_ALIVE_TIMEOUT;}
};
