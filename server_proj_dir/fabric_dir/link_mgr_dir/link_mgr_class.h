/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.h
*/

#pragma once

class LinkClass;
class SessionClass;
class FabricClass;

class LinkMgrClass {
#define LINK_MGR_LINK_ARRAY_SIZE 1000
#define LINK_MGR_MAX_GLOBAL_LINK_ID 9999

protected:
    friend class DFabricClass;

public:

    FabricClass *theFabricObject;
    int theGlobalLinkId;
    LinkClass *theLinkTableArray[LINK_MGR_LINK_ARRAY_SIZE + 4];

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

    LinkMgrClass(FabricClass *fabric_object_val);
    ~LinkMgrClass();
    char const* objectName(void) {return "LinkMgrClass";}

    void linkMgrLogit(char const* str0_val, char const* str1_val);
    void linkMgrAbend(char const* str0_val, char const* str1_val);

    FabricClass *fabricObject(void) {return this->theFabricObject;}

    void freeLink(LinkClass *link_object_val);
    LinkClass *searchLink(char *data_val);

    int allocLinkId(void);
    int allocLinkIndex(void);
    LinkClass *getLinkByIdIndex(int link_id_val, int link_index_val);
};
