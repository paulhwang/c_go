/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_class.h
*/

#pragma once
#include "../engine_class.h"
#include "../go_base_dir/go_base_class.h"

class EngineClass;
class GoBaseClass;

class DEngineClass {
    int debugOn_;
    EngineClass *engineObj_;
    void *thePortObject;

    void startNetConnect(void);
    void processSetupBase(char *data_al);
    void processPutBaseData(char *data_val);

public:
    DEngineClass(int debug_on_val, EngineClass *engine_obj_val);
    ~DEngineClass(void);
    char const* objectName(void) {return "DEngineClass";}

    void *portObject(void) {return this->thePortObject;}
    void xmtData(char *data_val);
    void processPutBaseDataResponse(GoBaseClass *base_object_val, char const *data_val);

    /* exports */
    void parseData(char *data_val);
};
