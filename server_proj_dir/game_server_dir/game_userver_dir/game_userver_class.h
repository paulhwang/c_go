/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_userver_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/base_mgr_protocol.h"

#define GAME_USERVER_RECEIVE_QUEUE_SIZE 100

class GameServerClass;

class GameUServerClass {

    void *theGameServerObject;
    void *theReceiveQueue;

    void debug(int on_off_val, char const* str0_val, char const* str1_val);
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GameUServerClass(GameServerClass *game_server_object_val);
    ~GameUServerClass(void);
    char const* objectName(void) {return "GameUServerClass";}
};
