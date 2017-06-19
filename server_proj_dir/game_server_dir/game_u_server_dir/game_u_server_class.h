/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_u_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../../protocol_dir/base_mgr_protocol.h"

class GameServerClass;

#define GAME_USERVER_RECEIVE_QUEUE_SIZE 100

class GameUServerClass {
    GameServerClass *theGameServerObject;
    void *theTpServerObject;
    void *theTpTransferObject;

    void baseMgrTest(void);
    void startNetServer(void);

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class GameDServerClass;
    friend class RoomMgrClass;

    void transmitFunction(char *data_val);

public:
    GameUServerClass(GameServerClass *game_server_object_val);
    ~GameUServerClass(void);
    char const* objectName(void) {return "GameUServerClass";}

    /* exports */
    void exportedNetReceiveFunction(char *data_val);
    void exportedNetAcceptFunction(void *tp_transfer_object_val);
};
