/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.h
*/

#pragma once

#include <pthread.h>
class QueueMgrClass;
class LinkClass;
#include "link_mgr_protocol.h"

#define LINK_MGR_RECEIVE_QUEUE_SIZE 100

class LinkMgrClass {
#define LINK_MGR_LINK_ARRAY_SIZE 1000
#define LINK_MGR_MAX_GLOBAL_LINK_ID 9999

    void *theMainObject;
    int theGlobalLinkId;
    LinkClass *linkTableArray[1000];
    LinkClass *theLinkTableArray[LINK_MGR_LINK_ARRAY_SIZE + 4];

    pthread_t theReceiveThread;
    QueueMgrClass *theReceiveQueue;

    int allocLinkId(void);
    int allocLinkIndex(void);
    void mallocLink(void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    LinkMgrClass(void *main_object_val);
    ~LinkMgrClass();
    char const* objectName(void) {return "LinkMgrClass";}
    pthread_t receiveThread(void) {return this->theReceiveThread;}

    /* exports */
    void exportReceiveData(void *data_val);

    void startThreads(void);
    void receiveThreadFunction(void);
    void receiveThreadLoop(void);
    void receiveData(char* data_val);
    void transmitData(char *data_val);

    void mallocLink (char const *my_name_val);
    void freeLink (LinkClass *link_object_val);

    void linkMgrLogit(char const* str0_val, char const* str1_val);
    void linkMgrAbend(char const* str0_val, char const* str1_val);
};
