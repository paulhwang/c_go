/*
  Copyrights reserved
  Written by Paul Hwang
  File name: link_mgr_class.h
*/

#pragma once

#include <pthread.h>
#include "link_mgr_protocol.h"
class QueueMgrClass;
class LinkClass;
class MainClass;
class TpTransferClass;

#define LINK_MGR_RECEIVE_QUEUE_SIZE 100

class LinkMgrClass {
#define LINK_MGR_LINK_ARRAY_SIZE 1000
#define LINK_MGR_MAX_GLOBAL_LINK_ID 9999

    MainClass *theMainObject;
    int theGlobalLinkId;
    LinkClass *theLinkTableArray[LINK_MGR_LINK_ARRAY_SIZE + 4];

    TpTransferClass *theTpTransferObject;
    pthread_t theTpServerThread;
    pthread_t theReceiveThread;
    QueueMgrClass *theReceiveQueue;

    void startReceiveThread(void);
    int allocLinkId(void);
    int allocLinkIndex(void);
    void mallocLink(void);

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    LinkMgrClass(MainClass *main_object_val);
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
