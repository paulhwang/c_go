/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.h
*/

#pragma once

class FabricClass;
class ThemeClass;
class EngineClass;
class TestClass;

class MainClass {
    FabricClass *theFabricObject;
    ThemeClass *theGoThemeObject;
    EngineClass *theEngineObject;
    TestClass *theTestObject;

    void debug(int on_off_val, char const *str0_val, char const *str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const *str0_val, char const *str1_val);
    void abend(char const *str0_val, char const *str1_val);

  public:
    MainClass(void);
    ~MainClass(void);
    char const *objectName(void) {return "MainClass";}
};
