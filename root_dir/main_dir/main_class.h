/*
  Copyrights reserved
  Written by Paul Hwang
  File name: main_class.h
*/

#pragma once
#include <pthread.h>

class TpClass;
class LinkMgrClass;
class BaseMgrClass;
class TpTransferClass;

class MainClass {
    TpClass *theTransportObject;
    LinkMgrClass *theLinkMgrObject;
    BaseMgrClass *theGoBaseMgrObject;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

  public:
    MainClass(void);
    ~MainClass(void);
    char const *objectName(void) {return "MainClass";}
    TpClass *transportObject(void) {return this->theTransportObject;}

    void startThreads(void);
};
