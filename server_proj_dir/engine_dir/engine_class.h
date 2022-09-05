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
    char const *objectName(void) {return "EngineClass";}
    int theDebugCode;
    
    DEngineClass *theDEngineObject;
    BaseMgrClass *theGoBaseMgrObject;
    void *theGoBaseListMgrObject;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

public:
    EngineClass(int debug_code_val);
    ~EngineClass(void);

    DEngineClass *dEngineObject(void) {return this->theDEngineObject;}
    BaseMgrClass *goBaseMgrObject(void) {return this->theGoBaseMgrObject;}

    GoBaseClass *mallocGoBase(char const *config_info_val);
    GoBaseClass *searchGoBase(char const *data_val) {return (GoBaseClass *) phwangListMgrSearchEntry(this->theGoBaseListMgrObject, data_val, 0);}
};
