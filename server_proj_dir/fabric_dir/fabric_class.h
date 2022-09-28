/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.h
*/

#pragma once
#include <pthread.h>

class MessengerClass;
class UFabricClass;
class DFabricClass;
class DbClass;
class LinkClass;
class GroupClass;
class SessionClass;
class NameListClass;

class FabricClass {
    char const *objectName(void) {return "FabricClass";}
    int theDebugCode;
    
    DbClass *theDbObject;
    MessengerClass *theMessengerObject;
    UFabricClass *theUFabricObject;
    DFabricClass *theDFabricObject;
    NameListClass *theNameListObject;
    void *theLinkListMgrObject;
    void *theGroupListMgrObject;
    pthread_t theWatchDogThread;

    void startWatchDogThread(void);
    void linkKeepAliveExamine(void);

public:
    FabricClass(int debug_code_val);
    ~FabricClass(void);

    DbClass *dbObject(void) {return this->theDbObject;}
    MessengerClass *messengerObject(void) {return this->theMessengerObject;}
    UFabricClass *uFabricObject(void) {return this->theUFabricObject;}
    DFabricClass *dFabricObject(void) {return this->theDFabricObject;}
    NameListClass *nameListObject(void) {return this->theNameListObject;}
    void *linkListMgrObject(void) {return this->theLinkListMgrObject;}

    void *watchDogThreadFunction(void);

    LinkClass *mallocLink(char const *my_name_val);
    void freeLink(LinkClass *link_object_val);
    LinkClass *searchLink(char *data_val, void *extra_data_val) {return (LinkClass *) phwangListMgrSearchEntry(this->theLinkListMgrObject, data_val, extra_data_val);}
    LinkClass *searchLinkByName(char *name_val);
    GroupClass *mallocGroup(
        char mode_val,
        char const *theme_info_val,
        char const *initiator_name_val,
        char const *peer_name_val);
    void freeGroup(GroupClass *group_object_val);
    GroupClass *searchGroup(char *data_val) {return (GroupClass *) phwangListMgrSearchEntry(this->theGroupListMgrObject, data_val, 0);}

    SessionClass *searchLinkByNameAndMallocSession(char *name_val);
    SessionClass *serachLinkAndSession(char *data_val);
};
