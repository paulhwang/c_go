/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.h
*/

#pragma once

#define LINK_MGR_RECEIVE_QUEUE_SIZE 100

#include "../../main_class.h"

class LinkMgrClass {
    void *mainObject;
    int globalLinkId;

    QueueMgrClass *receiveQueue;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    LinkMgrClass(void *main_object_val);
    ~LinkMgrClass();

    char const* objectName(void) {return "LinkMgrClass";}
    void startThreads(void);

    void linkMgrLogit(char const* str0_val, char const* str1_val);
    void linkMgrAbend(char const* str0_val, char const* str1_val);
};
