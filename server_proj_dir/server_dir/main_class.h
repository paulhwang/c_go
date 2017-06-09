/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.h
*/

#pragma once

class LinkMgrClass;
class BaseMgrClass;
class GameServerClass;

class MainClass {
    LinkMgrClass *theLinkMgrObject;
    BaseMgrClass *theGoBaseMgrObject;
    GameServerClass *theGoGameServerObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  public:
    MainClass(void);
    ~MainClass(void);
    char const *objectName(void) {return "MainClass";}

    void startThreads(void);
};
