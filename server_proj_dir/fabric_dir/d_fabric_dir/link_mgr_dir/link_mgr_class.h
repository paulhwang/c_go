/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.h
*/

#pragma once

#include "../d_fabric_class.h"
class LinkClass;
class DFabricClass;

class LinkMgrClass {
#define LINK_MGR_LINK_ARRAY_SIZE 1000
#define LINK_MGR_MAX_GLOBAL_LINK_ID 9999

    DFabricClass *theDFabricObject;
    int theGlobalLinkId;
    LinkClass *theLinkTableArray[LINK_MGR_LINK_ARRAY_SIZE + 4];

    int allocLinkId(void);
    int allocLinkIndex(void);
    LinkClass *getLinkByIdIndex(int link_id_val, int link_index_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    LinkMgrClass(DFabricClass *d_fabric_object_val);
    ~LinkMgrClass();
    char const* objectName(void) {return "LinkMgrClass";}
    DFabricClass *dFabricObject(void) {return this->theDFabricObject;}

    void transmitData1(char *data_val);

    void mallocLink (char const *my_name_val);
    void freeLink (LinkClass *link_object_val);

    void mallocSession (char *my_name_val);

    void linkMgrLogit(char const* str0_val, char const* str1_val);
    void linkMgrAbend(char const* str0_val, char const* str1_val);
};
