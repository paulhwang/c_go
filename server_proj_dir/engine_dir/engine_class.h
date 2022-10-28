/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.h
*/

#pragma once

class DEngineClass;
class BaseMgrClass;
class GoBaseClass;

class EngineClass {
public:
    int debugOn(void) {return true;}

private:
    int debugOn_;
    char const *objectName(void) {return "EngineClass";}
    int theDebugCode;
    
    DEngineClass *theDEngineObject;
    BaseMgrClass *theGoBaseMgrObject;
    void *theGoBaseListMgrObject;

public:
    EngineClass(int debug_on_val);
    ~EngineClass(void);

    DEngineClass *dEngineObject(void) {return this->theDEngineObject;}
    BaseMgrClass *goBaseMgrObject(void) {return this->theGoBaseMgrObject;}

    GoBaseClass *mallocGoBase(char *config_info_val);
    GoBaseClass *searchGoBase(char const *data_val) {return (GoBaseClass *) phwangListMgrSearchEntry(this->theGoBaseListMgrObject, data_val, 0);}
};
