/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.h
*/

#pragma once

class FabricClass;
class BaseMgrClass;
class ThemeClass;
class EngineClass;

class MainClass {
    FabricClass *theFabricObject;
    BaseMgrClass *theGoBaseMgrObject;
    ThemeClass *theGoThemeObject;
    EngineClass *theEngineObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  public:
    MainClass(void);
    ~MainClass(void);
    char const *objectName(void) {return "MainClass";}

    void startThreads(void);
};
