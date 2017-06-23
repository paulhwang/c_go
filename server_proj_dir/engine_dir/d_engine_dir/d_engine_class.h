/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_class.h
*/

#pragma once

class EngineClass;

class DEngineClass {
    EngineClass *theEngineObject;
    void *theTpTransferObject;

    void startNetConnect(void);
    void processMallocBase(char *data_al);
    void processTransferData(char *data_val);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:

    void transmitFunction(char *data_val);

public:
    DEngineClass(EngineClass *engine_object_val);
    ~DEngineClass(void);
    char const* objectName(void) {return "DEngineClass";}

    /* exports */
    void exportedparseFunction(char *data_val);
};
