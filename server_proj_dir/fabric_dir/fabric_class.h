/*
  Copyrights reserved
  Written by Paul Hwang
  File name: fabric_class.h
*/

#pragma once

class LinkMgrClass;
class GroupMgrClass;
class UFabricClass;
class DFabricClass;
class LinkClass;
class GroupClass;
class SessionClass;

class FabricClass {
    LinkMgrClass *theLinkMgrObject;
    GroupMgrClass *theGroupMgrObject;
    UFabricClass *theUFabricObject;
    DFabricClass *theDFabricObject;
    void *theLinkListMgrObject;
    void *theGroupListMgrObject;

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class LinkMgrClass;
    friend class SessionMgrClass;
    friend class GroupMgrClass;
    friend class UFabricClass;
    friend class DFabricClass;

    LinkMgrClass *linkMgrObject(void) {return this->theLinkMgrObject;}
    GroupMgrClass *groupMgrObject(void) {return this->theGroupMgrObject;}
    UFabricClass *uFabricObject(void) {return this->theUFabricObject;}
    DFabricClass *dFabricObject(void) {return this->theDFabricObject;}

    LinkClass *mallocLink(char const *my_name_val);
    GroupClass *mallocGroup(void);
    SessionClass *mallocSession(char *my_name_val);
    SessionClass *serachSession(char *data_val);

public:
    FabricClass(void);
    ~FabricClass(void);
    char const* objectName(void) {return "FabricClass";}
};
