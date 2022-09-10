/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_class.h
*/

#pragma once
#include "../go_base_dir/go_base_class.h"

class EngineClass;
class GoBaseClass;

class DEngineClass {
    EngineClass *theEngineObject;
    void *theTpTransferObject;

    void startNetConnect(void);
    void processSetupBase(char const *data_al);
    void processPutBaseData(char const *data_val);

public:
    DEngineClass(EngineClass *engine_object_val);
    ~DEngineClass(void);
    char const* objectName(void) {return "DEngineClass";}

    void transmitFunction(char *data_val);
    void processPutBaseDataResponse(GoBaseClass *base_object_val, char const *data_val);

    /* exports */
    void exportedParseFunction(char *data_val);
};
