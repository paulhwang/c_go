/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_server_class.h
*/

#pragma once

#include <pthread.h>
#include "../protocol_dir/base_mgr_protocol.h"
class RoomMgrClass;
class RoomClass;
class GameUServerClass;
class GameDServerClass;

class GameServerClass {
#define GAME_SERVER_ROOM_ARRAY_SIZE 32

    void *theMainObject;
    GameUServerClass *theGameUServerObject;
    GameDServerClass *theGameDServerObject;

    RoomMgrClass *theRoomMgrObject;
    RoomClass *theRoomTableArray[GAME_SERVER_ROOM_ARRAY_SIZE];

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GameServerClass(void *main_object_val);
    ~GameServerClass(void);
    char const* objectName(void) {return "GameServerClass";}
    GameUServerClass *gameUServerObject(void) {return this->theGameUServerObject;}
    GameDServerClass *gameDServerObject(void) {return this->theGameDServerObject;}

    /* exports */
    void startThreads(void);
    void receiveData(char* data_val);
    void transmitData(char *data_val);

    void insertRoom(RoomClass *room_object_val);
    void removeRoom(RoomClass *room_object_val);
};
