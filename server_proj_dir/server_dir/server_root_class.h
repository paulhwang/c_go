/*
  Copyrights reserved
  Written by Paul Hwang
  File name: server_root_class.h
*/

#pragma once

class FabricClass;
class ThemeClass;
class EngineClass;
class TestClass;

class ServerRootClass {
    FabricClass *theFabricObject;
    ThemeClass *theGoThemeObject;
    EngineClass *theEngineObject;
    TestClass *theTestObject;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

  public:
    ServerRootClass(int debug_code_val);
    ~ServerRootClass(void);
    char const *objectName(void) {return "ServerRootClass";}
};
