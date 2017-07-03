/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.h
*/

#pragma once

class UFabricClass;
class DFabricClass;
class LinkClass;
class GroupClass;
class SessionClass;
class NameListClass;

class FabricClass {
    UFabricClass *theUFabricObject;
    DFabricClass *theDFabricObject;
    NameListClass *theNameListObject;
    void *theLinkListMgrObject;
    void *theGroupListMgrObject;

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class UFabricClass;
    friend class DFabricClass;
    friend class NameListClass;

    void *linkListMgrObject(void) {return this->theLinkListMgrObject;}

    UFabricClass *uFabricObject(void) {return this->theUFabricObject;}
    DFabricClass *dFabricObject(void) {return this->theDFabricObject;}

    LinkClass *mallocLink(char const *my_name_val);
    void freeLink(LinkClass *link_object_val);
    LinkClass *searchLink(char *data_val) {return (LinkClass *) phwangListMgrSearchEntry(this->theLinkListMgrObject, data_val);}

    GroupClass *mallocGroup(char *theme_data_val);
    void freeGroup(GroupClass *group_object_val);
    GroupClass *searchGroup(char *data_val) {return (GroupClass *) phwangListMgrSearchEntry(this->theGroupListMgrObject, data_val);}

    SessionClass *searchLinkAndMallocSession(char *my_name_val);
    SessionClass *serachLinkAndSession(char *data_val);

public:
    FabricClass(void);
    ~FabricClass(void);
    char const* objectName(void) {return "FabricClass";}
};
