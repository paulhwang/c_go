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

    GameUServerClass *theGameUServerObject;
    GameDServerClass *theGameDServerObject;

    RoomMgrClass *theRoomMgrObject;
    RoomClass *theRoomTableArray[GAME_SERVER_ROOM_ARRAY_SIZE];

    void debug(int on_off_val, char const* str0_val, char const* str1_val) {if (on_off_val) this->logit(str0_val, str1_val);};
    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

protected:
    friend class GameUServerClass;
    friend class GameDServerClass;
    friend class RoomMgrClass;

    GameUServerClass *gameUServerObject(void) {return this->theGameUServerObject;}
    GameDServerClass *gameDServerObject(void) {return this->theGameDServerObject;}

public:
    GameServerClass(void);
    ~GameServerClass(void);
    char const* objectName(void) {return "GameServerClass";}

    /* exports */
    void receiveData(char* data_val);
    void transmitData(char *data_val);

    void insertRoom(RoomClass *room_object_val);
    void removeRoom(RoomClass *room_object_val);
};
