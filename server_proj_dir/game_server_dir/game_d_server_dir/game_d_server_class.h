/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_d_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/base_mgr_protocol.h"

#define GAME_DSERVER_RECEIVE_QUEUE_SIZE 100
#define GAME_DSERVER_GROUP_ARRAY_SIZE 32

class GameServerClass;

class GameDServerClass {
    void *theGameServerObject;
    void *theReceiveQueue;
    pthread_t theReceiveThread;
    void *theTpTransferObject;

    void startReceiveThread(void);
    void receiveThreadLoop(void);
    void receiveFunction(char *data_val);

    void debug(int on_off_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GameDServerClass(GameServerClass *game_server_object_val);
    ~GameDServerClass(void);
    char const* objectName(void) {return "GameDServerClass";}

    void startThreads(void);
    void receiveThreadFunction(void);
    void transmitFunction(char *data_val);
};
