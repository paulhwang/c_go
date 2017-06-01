/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.h
*/

#pragma once

class QueueMgrClass;
class LinkClass;

#define LINK_MGR_RECEIVE_QUEUE_SIZE 100

#include "../../main_class.h"

class LinkMgrClass {
    void *theMainObject;
    int theGlobalLinkId;
    LinkClass *linkTableArray[1000];

    pthread_t theReceiveThread;
    QueueMgrClass *theReceiveQueue;

    int allocLinkId (void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    LinkMgrClass(void *main_object_val);
    ~LinkMgrClass();
    char const* objectName(void) {return "LinkMgrClass";}

    /* exports */
    void exportReceiveData(void *data_val);

    void startThreads(void);
    void receiveThreadFunction(void);
    void receiveThreadLoop(void);

    LinkClass *mallocLink (char const *my_name_val);
    void freeLink (LinkClass *link_object_val);

    void linkMgrLogit(char const* str0_val, char const* str1_val);
    void linkMgrAbend(char const* str0_val, char const* str1_val);
};
