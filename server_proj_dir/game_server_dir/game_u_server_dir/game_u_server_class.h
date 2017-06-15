/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_u_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/base_mgr_protocol.h"

#define GAME_USERVER_RECEIVE_QUEUE_SIZE 100

class GameServerClass;

class GameUServerClass {

    void *theGameServerObject;
    void *theReceiveQueue;
    pthread_t theReceiveThread;
    void *theTpServerObject;
    void *theTpTransferObject;

    void startReceiveThread(void);
    void receiveThreadLoop(void);

    void baseMgrTest(void);
    
    void debug(int on_off_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GameUServerClass(GameServerClass *game_server_object_val);
    ~GameUServerClass(void);
    char const* objectName(void) {return "GameUServerClass";}

    /* exports */
    void exportAcceptConnectionFromBaseMgr(void *tp_transfer_object_val);
    void exportReceiveDataFromBaseMgr(void *data_val);

    void startThreads(void);
    void receiveThreadFunction(void);
    void receiveFunction(char *data_val);
    void transmitFunction(char *data_val);
};
