/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.h
*/

#pragma once

class LinkClass;
class DFabricClass;

#define LINK_MGR_RECEIVE_QUEUE_SIZE 100

class LinkMgrClass {
#define LINK_MGR_LINK_ARRAY_SIZE 1000
#define LINK_MGR_MAX_GLOBAL_LINK_ID 9999

    DFabricClass *theDFabricObject;
    int theGlobalLinkId;
    LinkClass *theLinkTableArray[LINK_MGR_LINK_ARRAY_SIZE + 4];

    void startReceiveThread(void);
    int allocLinkId(void);
    int allocLinkIndex(void);
    LinkClass *getLinkByIdIndex(int link_id_val, int link_index_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    LinkMgrClass(DFabricClass *d_fabric_object_val);
    ~LinkMgrClass();
    char const* objectName(void) {return "LinkMgrClass";}

    /* exports */
    void exportReceiveData(void *data_val);
    void exportAcceptConnection(void *tp_transfer_object_val);

    void receiveData(char* data_val);
    void transmitData(char *data_val);

    void mallocLink (char const *my_name_val);
    void freeLink (LinkClass *link_object_val);

    void mallocSession (char *my_name_val);

    void linkMgrLogit(char const* str0_val, char const* str1_val);
    void linkMgrAbend(char const* str0_val, char const* str1_val);
};
