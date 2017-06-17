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

class FabricClass {
    LinkMgrClass *theLinkMgrObject;
    GroupMgrClass *theGroupMgrObject;
    UFabricClass *theUFabricObject;
    DFabricClass *theDFabricObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class LinkMgrClass;
    friend class SessionMgrClass;
    friend class GroupMgrClass;
    friend class UFabricClass;
    friend class DFabricClass;

    char const* objectName(void) {return "FabricClass";}
    LinkMgrClass *linkMgrObject(void) {return this->theLinkMgrObject;}
    GroupMgrClass *groupMgrObject(void) {return this->theGroupMgrObject;}
    UFabricClass *uFabricObject(void) {return this->theUFabricObject;}
    DFabricClass *dFabricObject(void) {return this->theDFabricObject;}

public:
    FabricClass(void);
    ~FabricClass(void);
};
