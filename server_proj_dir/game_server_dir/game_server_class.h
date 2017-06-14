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

class GameServerClass {
#define GAME_SERVER_GROUP_ARRAY_SIZE 32

    void *theMainObject;
    GameUServerClass *theGameUServerObject;
    GameDServerClass *theGameDServerObject;

    GroupMgrClass *theGroupMgrObject;
    GroupClass *theGroupTableArray[GAME_SERVER_GROUP_ARRAY_SIZE];

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GameServerClass(void *main_object_val);
    ~GameServerClass(void);
    char const* objectName(void) {return "GameServerClass";}

    /* exports */
    void startThreads(void);
    void receiveData(char* data_val);
    void transmitData(char *data_val);

    void insertGroup(GroupClass *game_object_val);
    void removeGroup(GroupClass *game_object_val);
};
