/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../protocol_dir/base_mgr_protocol.h"
class GroupMgrClass;
class GroupClass;
class GameUServerClass;
class GameDServerClass;

#define GAME_SERVER_RECEIVE_QUEUE_SIZE 100

class GameServerClass {
#define GAME_SERVER_GROUP_ARRAY_SIZE 32

    void *theMainObject;
    GameUServerClass *theGameUServerObject;
    GameDServerClass *theGameDServerObject;

    void *theTpServerObject;
    GroupMgrClass *theGroupMgrObject;
    GroupClass *theGroupTableArray[GAME_SERVER_GROUP_ARRAY_SIZE];

    void *theTpTransferObject;
    pthread_t theReceiveThread;
    void *theReceiveQueue;

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GameServerClass(void *main_object_val);
    ~GameServerClass(void);
    char const* objectName(void) {return "GameServerClass";}

    void baseMgrTest(void);

    /* exports */
    void exportAcceptConnectionFromBaseMgr(void *tp_transfer_object_val);
    void exportReceiveDataFromBaseMgr(void *data_val);
    void exportReceiveDataFromLinkMgr(void *data_val);

    void startThreads(void);
    void startReceiveThread(void);
    void receiveThreadFunction(void);
    void receiveThreadLoop(void);
    void receiveData(char* data_val);
    void transmitData(char *data_val);

    void insertGroup(GroupClass *game_object_val);
    void removeGroup(GroupClass *game_object_val);
};
