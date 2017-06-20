/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_d_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/base_mgr_protocol.h"

class GameServerClass;

#define GAME_DSERVER_RECEIVE_QUEUE_SIZE 100
#define GAME_DSERVER_GROUP_ARRAY_SIZE 32

class GameServerClass;

class GameDServerClass {
    GameServerClass *theGameServerObject;
    void *theTpTransferObject;

    void startNetConnect(void);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class GameUServerClass;
    friend class RoomMgrClass;

    void transmitFunction(char *data_val);

public:
    GameDServerClass(GameServerClass *game_server_object_val);
    ~GameDServerClass(void);
    char const* objectName(void) {return "GameDServerClass";}

    /* exports */
    void exportedNetReceiveFunction(char *data_val);
};
