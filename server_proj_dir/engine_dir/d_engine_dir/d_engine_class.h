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

    void debug(int debug_on_val, char const *func_name_val, char const *str1_val);
    void debug2(int debug_on_val, char const *func_name_val, char const *str1_val, char const *str2_val);
    void debugInt(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val);
    void debugInt2(int debug_on_val, char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void logit(char const *func_name_val, char const *str1_val);
    void logit2(char const *func_name_val, char const *str1_val, char const *str2_val);
    void logitInt(char const *func_name_val, char const *str1_val, int int1_val);
    void logitInt2(char const *func_name_val, char const *str1_val, int int1_val, char const *str2_val, int int2_val);
    void abend(char const *func_name_val, char const *str1_val);
    void abend2(char const *func_name_val, char const *str1_val, char const *str2_val);

public:
    DEngineClass(EngineClass *engine_object_val);
    ~DEngineClass(void);
    char const* objectName(void) {return "DEngineClass";}

    void transmitFunction(char *data_val);
    void processPutBaseDataResponse(GoBaseClass *base_object_val, char const *data_val);

    /* exports */
    void exportedParseFunction(char *data_val);
};
