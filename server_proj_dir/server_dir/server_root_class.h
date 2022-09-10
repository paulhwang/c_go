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

  public:
    ServerRootClass(int debug_code_val);
    ~ServerRootClass(void);
    char const *objectName(void) {return "ServerRootClass";}
};
