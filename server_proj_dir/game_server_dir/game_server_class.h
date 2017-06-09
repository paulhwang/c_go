/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_server_class.h
*/

#pragma once

class GroupMgrClass;
class GroupClass;

class GameServerClass {
#define GAME_SERVER_GROUP_ARRAY_SIZE 32

    void *theMainObject;
    GroupMgrClass *theGroupMgrObject;
    GroupClass *theGroupTableArray[GAME_SERVER_GROUP_ARRAY_SIZE];

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);

public:
    GameServerClass(void *main_object_val);
    ~GameServerClass(void);
    char const* objectName(void) {return "GameServerClass";}

    void startThreads(void);
    
    void insertGroup(GroupClass *game_object_val);
    void removeGroup(GroupClass *game_object_val);
};
