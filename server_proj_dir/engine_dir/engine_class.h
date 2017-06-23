/*
  Copyrights reserved
  Written by Paul Hwang
  File name: engine_class.h
*/

#pragma once

class DEngineClass;
class BaseMgrClass;

class EngineClass {
    DEngineClass *theDEngineObject;
    BaseMgrClass *theGoBaseMgrObject;

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    EngineClass(void);
    ~EngineClass(void);
    char const* objectName(void) {return "EngineClass";}
};
