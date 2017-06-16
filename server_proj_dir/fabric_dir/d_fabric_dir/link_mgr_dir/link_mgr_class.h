/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.h
*/

#pragma once

#include "../d_fabric_class.h"
class LinkClass;
class FabricClass;

class LinkMgrClass {
#define LINK_MGR_LINK_ARRAY_SIZE 1000
#define LINK_MGR_MAX_GLOBAL_LINK_ID 9999

    FabricClass *theFabricObject;
    int theGlobalLinkId;
    LinkClass *theLinkTableArray[LINK_MGR_LINK_ARRAY_SIZE + 4];

    int allocLinkId(void);
    int allocLinkIndex(void);
    LinkClass *getLinkByIdIndex(int link_id_val, int link_index_val);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    LinkMgrClass(FabricClass *fabric_object_val);
    ~LinkMgrClass();
    char const* objectName(void) {return "LinkMgrClass";}
    FabricClass *fabricObject(void) {return this->theFabricObject;}

    void mallocLink (char const *my_name_val);
    void freeLink (LinkClass *link_object_val);

    void mallocSession (char *my_name_val);

    void linkMgrLogit(char const* str0_val, char const* str1_val);
    void linkMgrAbend(char const* str0_val, char const* str1_val);
};
